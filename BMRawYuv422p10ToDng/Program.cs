﻿using System;

namespace BMRawAVIv210ToDng {
    class Program {
        static void Main(string[] args) {
            if (args.Length != 2) {
                Console.WriteLine("Usage: BMRawYuv420p10ToDng fromYuv420p10ImageFilePath toDngFilePathTemplate");
                return;
            }

            var conv = new Convert();
            conv.Run(args[0], args[1]);
        }
    }
}
