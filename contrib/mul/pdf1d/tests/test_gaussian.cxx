//:
// \file
// \author Tim Cootes
// \brief test pdf1d_gaussian, building, sampling, saving etc.

#include <vcl_iostream.h>
#include <vcl_cmath.h> // for vcl_fabs()

#include <pdf1d/pdf1d_gaussian.h>
#include <pdf1d/pdf1d_gaussian_builder.h>
#include <pdf1d/pdf1d_gaussian_sampler.h>
#include <mbl/mbl_data_array_wrapper.h>
#include <vsl/vsl_binary_loader.h>
#include <vnl/vnl_test.h>

//=======================================================================


//: Generate lots of samples using pdf, build new pdf with builder and compare the two
void test_gaussian()
{
  vcl_cout << "\n\n************************\n";
  vcl_cout << " Testing pdf1d_gaussian\n";
  vcl_cout << "************************\n";

  vsl_add_to_binary_loader(pdf1d_gaussian());
  vsl_add_to_binary_loader(pdf1d_gaussian_builder());

  pdf1d_gaussian_builder builder;

  pdf1d_gaussian pdf(1,2);

// Test builder =======================================
  int n_samples = 10000;

  pdf1d_sampler* p_sampler = pdf.new_sampler();

// Generate lots of samples
  vcl_vector<double> data(n_samples);
  for (int i=0;i<n_samples;++i)
    data[i] = p_sampler->sample();

  pdf1d_pdf* p_pdf_built = builder.new_model();

  mbl_data_array_wrapper<double> data_array(&data[0],n_samples);

  builder.build(*p_pdf_built,data_array);

  vcl_cout<<"Original PDF: "; vsl_print_summary(vcl_cout, pdf); vcl_cout<<vcl_endl;
  vcl_cout<<"Rebuilt PDF: "; vsl_print_summary(vcl_cout, p_pdf_built); vcl_cout<<vcl_endl;
  vcl_cout<<vcl_endl;
  vcl_cout<<"PDF sampler: "; vsl_print_summary(vcl_cout, p_sampler); vcl_cout<<vcl_endl;

// Test the IO ================================================

  pdf1d_builder* p_builder = & builder;
  pdf1d_pdf* p_pdf = & pdf;

  TEST("Mean of built model",vcl_fabs(pdf.mean()-p_pdf_built->mean())<0.1,true);
  TEST("Variances",vcl_fabs(pdf.variance()-p_pdf_built->variance())<0.1,true);

  vcl_cout<<"\n\n=================Testing I/O:\nSaving data...\n";
  vsl_b_ofstream bfs_out("test_gaussian.bvl.tmp");
  TEST ("Created test_gaussian.bvl.tmp for writing", (!bfs_out), false);

  vsl_b_write(bfs_out,pdf);
  vsl_b_write(bfs_out,builder);
  vsl_b_write(bfs_out,p_pdf);
  vsl_b_write(bfs_out,p_builder);
  bfs_out.close();

  pdf1d_gaussian          pdf_in;
  pdf1d_gaussian_builder  builder_in;
  pdf1d_pdf*         p_pdf_in = NULL;
  pdf1d_builder*     p_builder_in = NULL;

  vsl_b_ifstream bfs_in("test_gaussian.bvl.tmp");
  TEST ("Opened test_gaussian.bvl.tmp for reading", (!bfs_in), false);

  vsl_b_read(bfs_in, pdf_in);
  vsl_b_read(bfs_in, builder_in);
  vsl_b_read(bfs_in, p_pdf_in);
  vsl_b_read(bfs_in, p_builder_in);
  TEST ("Finished reading file successfully", (!bfs_in), false);
  bfs_in.close();

  vcl_cout<<"Original PDF: "; vsl_print_summary(vcl_cout, pdf); vcl_cout<<vcl_endl;
  vcl_cout<<"Original builder: "; vsl_print_summary(vcl_cout, builder); vcl_cout<<vcl_endl;
  vcl_cout<<vcl_endl;

  vcl_cout<<"Loaded PDF: "; vsl_print_summary(vcl_cout, pdf_in); vcl_cout<<vcl_endl;
  vcl_cout<<"Loaded builder: "; vsl_print_summary(vcl_cout, builder_in); vcl_cout<<vcl_endl;
  vcl_cout<<vcl_endl;

  TEST("Original Model == Loaded model",
       pdf.mean()==pdf_in.mean() &&
       pdf.variance()==pdf_in.variance() &&
       pdf.log_k() == pdf_in.log_k(),
       true);
  TEST("Original Model == model loaded by base ptr",
       pdf.mean()==p_pdf_in->mean() &&
       pdf.variance()==p_pdf_in->variance() &&
       pdf.is_a()==p_pdf_in->is_a(),
       true);
  TEST("Original Builder == Loaded builder",
       builder.min_var()==builder_in.min_var(),
       true);
  TEST("Original Builder == Builder loaded by base ptr",
       builder.min_var()==p_builder_in->min_var() &&
       builder.is_a()==p_builder_in->is_a(),
       true);

  vcl_cout << "========Testing PDF Thresholds==========";
  pdf1d_sampler *p_sampler2 = p_pdf_built->new_sampler();
  unsigned pass=0, fail=0;
  double thresh = p_pdf_built->log_prob_thresh(0.9);
  vcl_cout << vcl_endl << "log density threshold for passing 90%: " << thresh << vcl_endl;
  for (unsigned i=0; i < 1000; i++)
  {
    double x = p_sampler2->sample();
    if (p_pdf_built->log_p(x) > thresh)
      pass ++;
    else
      fail ++;
  }
  vcl_cout << "In a sample of 1000 vectors " << pass << " passed and " << fail <<  " failed.\n";
  TEST("880 < pass < 920", pass > 880 && pass < 920, true);
  pass=0; fail=0;
  thresh = p_pdf_built->log_prob_thresh(0.1);
  vcl_cout << vcl_endl << vcl_endl << "log density threshold for passing 10%: " << thresh << vcl_endl;
  for (unsigned i=0; i < 1000; i++)
  {
    double x = p_sampler2->sample();
    if (p_pdf_built->log_p(x) > thresh)
      pass ++;
    else
      fail ++;
  }
  vcl_cout << "In a sample of 1000 vectors " << pass << " passed and " << fail <<  " failed.\n";
  TEST("70 < pass < 130", pass > 70 && pass < 130, true);
  delete p_sampler2;


  delete p_pdf_built;
  delete p_sampler;
  delete p_pdf_in;
  delete p_builder_in;
}

TESTMAIN(test_gaussian);
