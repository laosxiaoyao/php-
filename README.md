# php扩展common
学习扩展开发，需要一点c基础


1. 使用php源码进入 ext目录
2. 使用./ext_skel --name=common
3. 编辑config.m4 去掉这两行的dnl  
PHP_ARG_WITH(common, for common support,
[  --with-common   Include common support])
4. 编辑common.c 文件
5. 使用/usr/local/php/bin/phpize 生成 configure
6. ./configure --with-php-config=/usr/local/php/bin/php-config
7. make && make install
8. 生成common.so  加入 php.ini中
9. 测试
10. var_dump((date('Y-m-d',c_strtotime('2019-01-02'))));
11. var_dump(c_getTwoDateDays("2019-07-02","2019-07-05"));
12. print_r(c_getTwoDates('2019-07-01','2019-07-30'));
