# php-
学习扩展开发，需要一点c基础


1. 使用php源码进入 ext目录
2. 使用./ext_skel --name=common
3. 编辑common.c 文件
4. 使用/usr/local/php/bin/phpize 生成 configure
5. ./configure --with-php-config=/usr/local/php/bin/php-config
6. make && make install
7. 生成common.so  加入 php.ini中
