#include <iostream>
#include <vector>
#include <random>
#include <fstream>

//other than apple :p
#include <CL/cl.hpp>
#define SIZE 1024


std::string load_program(std::string input) {
  std::ifstream stream(input.c_str());
  if (!stream.is_open()) {
    std::cout << "Cannot open file: " << input << std::endl;
    exit(1);
  }
  return std::string(std::istreambuf_iterator<char>(stream),
                     (std::istreambuf_iterator<char>()));
}

int main()
{
    std::vector<cl::Platform> all_platforms;
    cl::Platform::get(&all_platforms);
    std::cout<<all_platforms.size()<<std::endl;
    if (all_platforms.size()==0) {
        std::cout<<" No platforms found. Check OpenCL installation!\n";
        exit(1);
    }
    cl::Platform default_platform=all_platforms[0];
    
    std::vector<float> h_a(SIZE);
    std::vector<float> h_b(SIZE);
    std::vector<float> h_c(SIZE);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dis(-0.5,0.5);  
    std::vector<cl::Device> all_devices;
    default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);

    for(std::size_t i = 0;i<SIZE;i++)
    {
        h_a[i] = dis(mt);
        h_b[i] = dis(mt);
        h_c[i] = dis(mt);
    }

    cl::Buffer d_a;
    cl::Buffer d_b;
    cl::Buffer d_c;

    cl::Context context(CL_DEVICE_TYPE_DEFAULT);
    cl::Program program(context , load_program("vadd.cl"));

    d_a = cl::Buffer(h_a.begin(), h_a.end(),true,false,nullptr);
    d_b = cl::Buffer(h_b.begin(), h_b.end(),true,false,nullptr);
    d_c = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * SIZE);
    cl::Device default_device=all_devices[0];
    cl::CommandQueue queue(context,default_device);
    auto vadd =
      cl::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer, int>(program, "vadd");

    vadd(cl::EnqueueArgs(queue, cl::NDRange(SIZE)), d_a, d_b, d_c, SIZE);
    queue.finish();
    cl::copy(d_c,h_c.begin(),h_c.end());


    return {};
}