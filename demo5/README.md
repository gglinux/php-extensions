# php-extensions
PHP HashTable使用

## Requirement
PHP 5.2 +

## Install
### Linux 编译安装
```
$ /$path/phpize
$ ./configure
$ make && make install
$ //添加生成的 gglinux.so 到 php.ini

```
### Document
config.m4为配置定义文件，用来读取编译命令。

./modules/gglinux.so 为编译后生成的二进制文件。

test.php 测试文件。

代码在gglinux.c中，编译完成并且加入到php.ini后。

运行 $ php test.php。输出 见注释。


[demo1](https://github.com/gglinux/php-extensions/demo1):扩展开发-基本结构

[demo2](https://github.com/gglinux/php-extensions/demo2):扩展开发-独立函数

[demo3](https://github.com/gglinux/php-extensions/demo3):扩展开发-使用返回值

[demo4](https://github.com/gglinux/php-extensions/demo4):扩展开发-获取函数参数

[demo5](https://github.com/gglinux/php-extensions/demo5):扩展开发-内部HashTable使用


### More
[PHP扩展开发及内核应用](http://www.cunmou.com/)
