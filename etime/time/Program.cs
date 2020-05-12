using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using System.ComponentModel;
using FILETIME = System.Runtime.InteropServices.ComTypes.FILETIME;

namespace time
{
    class Program
    {
        public class QueryPerfCounter
        {
            private long start;
            private long stop;
            private long frequency;
            Decimal multiplier = new Decimal(1.0e9);

            public void Start()
            {
                QueryPerformanceCounter(out start);
            }

            public void Stop()
            {
                QueryPerformanceCounter(out stop);
            }

            //  returns in ms
            public double Duration()
            {
                return ((((double)(stop - start) *
                          (double)multiplier) /
                          (double)frequency)) / 1000000;
            }

            public QueryPerfCounter()
            {
                if (QueryPerformanceFrequency(out frequency) == false)
                {
                    // Frequency not supported
                    throw new Win32Exception();
                }
            }

            [DllImport("KERNEL32")]
            private static extern bool QueryPerformanceCounter(out long lpPerformanceCount);

            [DllImport("Kernel32.dll")]
            private static extern bool QueryPerformanceFrequency(out long lpFrequency);
        }
        

        class ProcessTime
        {
            public ProcessTime(System.Diagnostics.Process proc)
            {
                FILETIME creationTime, exitTime;
                GetProcessTimes(proc.Handle, out creationTime, out exitTime, out _krnlTime, out _userTime);
            }

            //  two - one
            public static TimeSpan DiffUserTime(ProcessTime one, ProcessTime two)
            {
                var one_userTime = FileTimeToDateTime(one._userTime);
                var two_userTime = FileTimeToDateTime(two._userTime);
                return two_userTime.Subtract(one_userTime);
            }

            public static TimeSpan DiffKrnlTime(ProcessTime one, ProcessTime two)
            {
                var one_krnlTime = FileTimeToDateTime(one._krnlTime);
                var two_krnlTime = FileTimeToDateTime(two._krnlTime);
                return two_krnlTime.Subtract(one_krnlTime);
            }

            private FILETIME _userTime;
            private FILETIME _krnlTime;

            static DateTime FileTimeToDateTime(FILETIME ftime)
            {
                long hFT2 = (((long)ftime.dwHighDateTime) << 32) + ftime.dwLowDateTime;
                DateTime dte = DateTime.FromFileTime(hFT2);
                return dte;
            }

            [DllImport("kernel32.dll", SetLastError = true)]
            [return: MarshalAs(UnmanagedType.Bool)]
            static extern bool GetProcessTimes(IntPtr hProcess,
                                               out FILETIME lpCreationTime,
                                               out FILETIME lpExitTime,
                                               out FILETIME lpKernelTime,
                                               out FILETIME lpUserTime);

        }

        static void Main(string[] args)
        {
            if (args.Length < 1)
                return;

            var cmd = string.Join(" ", args);

            var procStartInfo = new System.Diagnostics.ProcessStartInfo();
            procStartInfo.FileName = "cmd.exe";
            procStartInfo.Arguments = "/C " + cmd;
            procStartInfo.UseShellExecute = false;
            procStartInfo.RedirectStandardError = true;
            procStartInfo.RedirectStandardInput = true;
            procStartInfo.RedirectStandardOutput = true;

            var process = new System.Diagnostics.Process();
            process.StartInfo = procStartInfo;
            process.OutputDataReceived += (sender, dataReceivedArgs) => Console.WriteLine(dataReceivedArgs.Data); 
            process.ErrorDataReceived += (sender, dataReceivedArgs) => Console.WriteLine(dataReceivedArgs.Data);

            QueryPerfCounter timer = new QueryPerfCounter();
            timer.Start();
            {
                process.Start();
                process.BeginOutputReadLine();
                process.WaitForExit();
                process.CancelOutputRead();
            }
            timer.Stop();

            Console.WriteLine("Time elapsed: {0} ms", timer.Duration().ToString("F"));
        }
    }
}
