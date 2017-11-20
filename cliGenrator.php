<?php
chdir(__DIR__);
        $i = 1;
        while($i<51){
                $cmd = "./test  ~/zids/".$i.".txt" .$i*1000" ;
                $outputfile = "./result.txt";
                $pidfile = "./pid.txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i));

                $cmd = "./test  500 ../zid/".($i+1).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+1));

                $cmd = "./test  500 ../zid/".($i+2).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+2));

                $cmd = "./test  500 ../zid/".($i+3).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+3));

                $cmd = "./test  500 ../zid/".($i+4).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+4));

                $cmd = "./test  500 ../zid/".($i+5).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+5));

                $cmd = "./test  500 ../zid/".($i+6).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+6));

                $cmd = "./test  500 ../zid/".($i+7).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+7));

                $cmd = "./test  500 ../zid/".($i+8).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+8));

                $cmd = "./test  500 ../zid/".($i+9).".txt";
                shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $cmd, $outputfile, $pidfile));
                print("\n".date("Y-m-d H:i:s")." - Running ".($i+9));

                sleep(60);
                $i+=10;
        }
?>
