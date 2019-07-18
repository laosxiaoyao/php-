/*
  +----------------------------------------------------------------------+
  | PHP Version 5.6                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:    xiaoyao                                                     |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_common.h"

#define DAY 86400

/* If you declare any globals in php_common.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(common)
*/
static int le_common;

PHP_MINIT_FUNCTION(common)
{
	return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(common)
{
	return SUCCESS;
}

PHP_RINIT_FUNCTION(common)
{
	return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(common)
{
	return SUCCESS;
}


time_t c_getTime(char * s)
{
	struct tm tm_date;
	sscanf(s, "%4d-%2d-%2d", &tm_date.tm_year, &tm_date.tm_mon, &tm_date.tm_mday);
	tm_date.tm_year -=  1900;
	tm_date.tm_mon--;
	tm_date.tm_hour = tm_date.tm_min = tm_date.tm_sec = 1;
	time_t time = mktime(&tm_date); 
	return time;
}

/*
	此函数功能跟 php中strtotime类似 传入date--'2019-01-01' 获取时间戳
*/
PHP_FUNCTION(c_strtotime)
{
	char *arg = NULL;
	int arg_len;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}
	
	time_t time = c_getTime(arg);
    RETVAL_LONG(time);
}

/*
用法 c_getTwoDates('2019-01-01', '2019-01-06');
返回2个日期的 所有日期 ，例如返回2019-01-02/03/04/05
*/
PHP_FUNCTION(c_getTwoDates){
	char *arg1 = NULL;
	char *arg2 = NULL;
	int arg1_len, arg2_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &arg1, &arg1_len, &arg2, &arg2_len) == FAILURE) {
		return;
	}

	time_t time1 = c_getTime(arg1);
	time_t time2 = c_getTime(arg2);
	time_t tmp = 0;
	if (time1 > time2) {
		tmp = time1;
		time1 = time2;
		time2 = tmp;
	}
	int i = 0;
	time_t t = time2;
	time_t day = DAY;
	struct tm tm;
	char buffer[13];
	array_init(return_value);
	while (t - day > time1) {
		memset(buffer, 0, sizeof(buffer));
		time_t t_d = time1 + day * (i + 1);
		strftime(buffer, sizeof(buffer), "%Y-%m-%d", localtime(&t_d));
		t -= day;
		i++;
		add_next_index_string(return_value, buffer, i);
	}
}

/*
用法 c_getTwoDates('2019-01-01', '2019-01-06');
返回2个日期的天数
*/
PHP_FUNCTION(c_getTwoDateDays)
{
	char *arg1 = NULL;
	char *arg2 = NULL;
	int arg1_len, arg2_len;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ss", &arg1, &arg1_len, &arg2, &arg2_len) == FAILURE) {
		return;
	}

	time_t time1 = c_getTime(arg1);
	time_t time2 = c_getTime(arg2);
	double s = difftime(time2, time1)/DAY;
	RETURN_LONG(s);
}


PHP_MINFO_FUNCTION(common)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "common support", "enabled");
	php_info_print_table_end();
}

const zend_function_entry common_functions[] = {
	PHP_FE(c_getTwoDateDays, NULL)
	PHP_FE(c_strtotime, NULL)
	PHP_FE(c_getTwoDates, NULL)
	PHP_FE_END	/* Must be the last line in common_functions[] */
};

/* {{{ common_module_entry
 */
zend_module_entry common_module_entry = {
	STANDARD_MODULE_HEADER,
	"common",
	common_functions,
	PHP_MINIT(common),
	PHP_MSHUTDOWN(common),
	PHP_RINIT(common),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(common),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(common),
	PHP_COMMON_VERSION,
	STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_COMMON
ZEND_GET_MODULE(common)
#endif


