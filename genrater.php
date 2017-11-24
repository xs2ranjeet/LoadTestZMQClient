<?php
$fileName = (isset($argv[1]) && $argv[1]!="")? $argv[1] : -1; "zid1.txt";
$start = (isset($argv[2]) && $argv[2]>=0)? $argv[2] : -1;
$end = (isset($argv[3]) && $argv[3]>=0)? $argv[3] : 500;
$count = (isset($argv[4]) && $argv[4]>=0)? $argv[4] : 500;
$outputfile = "./result.txt";
$pidfile = "./pid.txt";

while ($start <= $end) {
	$command = "./test ".$fileName." ".($start+1)." ".($start+$count)." ".$count;
	$start = $count + $start;
    shell_exec(sprintf("%s > %s 2>&1 & echo $! >> %s", $command, $outputfile, $pidfile));
    print("\n".date("Y-m-d H:i:s")." - Running ".($start));
	//exec($command);
	if($start % 25001 == 0)
		sleep(60);
}
?>