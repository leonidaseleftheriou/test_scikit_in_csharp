using System;
using System.Runtime.InteropServices;
using System.IO;
using System.Linq;
using System.Collections;
using System.Collections.Generic;

namespace ConsoleApplication
{
    public class TestEmbedding
    {
        [DllImport("libtest.so")]
        static extern IntPtr initialize_classifier(string script, string function);
        [DllImport("libtest.so")]
        static extern IntPtr train(string script, string function, double [] arguments, int totalsize, int numOfDatapoints, IntPtr classifier, IntPtr coeff_ptr);
        [DllImport("libtest.so")]
        static extern IntPtr return_results(string script, string function, IntPtr classifier);
        public static void Main(string[] args)
        {
            IEnumerable<string> [] fi = new IEnumerable<string> [3];

            //data are 2-dimensional (bl_big_1 and bl_big_2 respectively) and bl2_big_cl contains the class
            //of the corresponding data
            
            //files bl2_big_1, 2, and cl.csb contain data in the same format as in all the files in the test
            //folder in the IDEA project
            fi[0] = File.ReadLines("bl2_big_1.csv");
            fi[1] = File.ReadLines("bl2_big_2.csv");
            fi[2] = File.ReadLines("bl2_big_cl.csv");
            List<string> [] list1= new List<string> [3];
            list1[0] = fi[0].ToList();
            list1[1] = fi[1].ToList();
            list1[2] = fi[2].ToList();
            list1[0].Remove(list1[0][0]);
            list1[1].Remove(list1[1][0]);
            list1[2].Remove(list1[2][0]);
            List<double> [] result1 = new List<double> [3];
            double[][] result2 = new double[3][];
            result1[0] = list1[0].Select(x => double.Parse(x)).ToList();
            result1[1] = list1[1].Select(x => double.Parse(x)).ToList();
            result1[2] = list1[2].Select(x => double.Parse(x)).ToList();
            result2[0] = result1[0].Cast<double>().ToArray();
            result2[1] = result1[1].Cast<double>().ToArray();
            result2[2] = result1[2].Cast<double>().ToArray();

            var batch_size = 1000;
            var numOfAttributes = 2;
            var n_iterations = (int)Math.Ceiling((double)result1[0].Count/batch_size);

            //initialize the classifier
            var classifier = initialize_classifier("initialize_classifier_script", "initialize_classifier"); //classifier = pointer to the classifier
            Console.Write("successfully made it through the initial call \n\n");
            var coeff = new double[3];
            var coeff2 = new double[3];
            IntPtr coeff_ptr = Marshal.AllocHGlobal(3 * sizeof(double)); //coeff_ptr = pointer to the results that we'll try to return by reference
            IntPtr coeff_ptr2 = Marshal.AllocHGlobal(3 * sizeof(double)); //coeff_ptr2 = pointer to the results that we'll try to return by value
            var z = new double[batch_size * (numOfAttributes+1)];
            
            //IntPtr classifier_ptr = new IntPtr();
            
            for (int i = 0; i<n_iterations; i++) {
                Console.Write("iteration = " + i + "\n");
                
                result1[0].Skip(i*batch_size).Take(batch_size).ToArray().CopyTo(z,0);
                result1[1].Skip(i*batch_size).Take(batch_size).ToArray().CopyTo(z,batch_size);
                result1[2].Skip(i*batch_size).Take(batch_size).ToArray().CopyTo(z,2*batch_size);
                
                //print the pointers
                Console.Write("classifier:"+classifier+"\n");
                Console.Write("coeff_ptr:"+coeff_ptr+"\n");
        
                //test_scikit_in_python3b("paok6", "paok6", z, z.Length, 1000, classifier, coeff_ptr);
                //pass a pointer to the classifier and a pointer to the results, in order to get them back by reference,
                //according to Carsten's instructions
                train("train_script", "train", z, z.Length, 1000, classifier, coeff_ptr);
                Console.Write("successfully returned from the train stage \n");

                coeff_ptr2 = return_results("return_results_script", "return_results", classifier); //COMMENT OUT IF YOU WANT AN ERROR-FREE EXECUTION
                
                string line1 = File.ReadLines("test.txt").First(); //read coeffs from text
                Marshal.Copy(coeff_ptr, coeff, 0, 3); //copy coeffs returned by reference
                Marshal.Copy(coeff_ptr2, coeff2, 0, 3); //copy coeffs returned by value, COMMENT OUT IF YOU WANT AN ERROR-FREE EXECUTION
                
                Console.Write("coefficients read from file as string = " + line1 + "\n");
                Console.Write("coefficients returned by reference= " + coeff[0] + " " + coeff[1] + " " + coeff[2] + "\n");
                Console.Write("coefficients returned by reference= " + coeff2[0] + " " + coeff2[1] + " " + coeff2[2] + "\n"); //COMMENT OUT IF YOU WANT AN ERROR-FREE EXECUTION
                Console.Write("\n");
            }
            
           
        }
    }
}
