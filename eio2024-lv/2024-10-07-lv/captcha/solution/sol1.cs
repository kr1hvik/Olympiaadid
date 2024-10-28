using System;
using System.Diagnostics;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Captcha
{
    internal class Program
    {
        static void Main(string[] args)
        {
            if (args.Length > 0)
            {
                SolveAll();
            }
            else
            {
                List<string> input = new List<string>();
                for(int i = 0; i < 6; i++)
                    input.Add(Console.ReadLine());
                for(int i = 0; i < int.Parse(input[5]); i++)
                    input.Add(Console.ReadLine());
                
                Console.WriteLine(Solve(input.ToArray()));
            }
        }

        private static void SolveAll()
        {
            int i = 0;
            while (File.Exists($"input{i}.txt"))
            {
                SolveFile($"input{i}.txt", $"output{i}.txt");
                i++;
            }
        }

        private static void SolveFile(string inputFile, string outputFile)
        {
            Console.WriteLine(inputFile);
            var lines = File.ReadAllLines(inputFile);
            var res = Solve(lines);
            File.WriteAllText(outputFile, res);
        }
        
        private static string Solve(string[] input)
        {
            int[] clicks = new int[5];
            Dictionary<string, int> labels = new Dictionary<string, int>();
            for (int i = 0; i < 5; i++)
            {
                labels[input[i]] = i;
            }

            int numClicks = int.Parse(input[5]);
            for (int i = 6; i < numClicks + 6; i++)
            {
                Click(clicks, labels[input[i]]);
            }

            List<int> log = new List<int>();
            
            for (int i = 0; i < 5; i++)
            {
                if (clicks[i] == 0)
                {
                    Click(clicks, i, log);
                }
                for (int j = i + 1; j < 5; j++)
                {
                    if (clicks[j] > 0 && (clicks[j] <= i+1 || clicks[j] < clicks[i]))
                    {
                        Click(clicks, j, log);
                    }
                }

                if (clicks[i] != i + 1)
                {
                    Console.WriteLine("!");
                }
            }

            return log.Count + Environment.NewLine + 
                   string.Join(Environment.NewLine, log.Select(n => input[n])) + Environment.NewLine;
        }

        private static void Click(int[] clicks, int n, List<int> log = null)
        {
            if (clicks[n] == 0)
            {
                clicks[n] = clicks.Max() + 1;
            }
            else
            {
                for (int j = 0; j < 5; j++)
                {
                    if (j != n && clicks[j] > clicks[n]) clicks[j]--;
                }

                clicks[n] = 0;
            }

            log?.Add(n);
        }
    }
}