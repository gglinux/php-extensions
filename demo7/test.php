<?php
$fp_in = gglinux_fopen("test_file.txt", "r") or die("Unable to open input file\n");
 
$fp_out = gglinux_fopen("test_file_new.txt", "w") or die("Unable to open output file\n");
 
while (!gglinux_eof($fp_in)) {
     $str = gglinux_fread($fp_in, 10);
     print($str);
     gglinux_fwrite($fp_out, $str);
} 
gglinux_fclose($fp_in);
gglinux_fclose($fp_out);

/*
输出：

hello!
PHP 最好的语言!!
haha!!!
66666!!!!

*/