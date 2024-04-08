# DDL

## 操作
**SHOW DATABASES;**
查询数据库<br>
**SELECT DATABASE();**
查询当前数据库<br>
**CREATE DATABASE 库名;**
创建<br>
**DROP DATABASE 库名;**
删除<br>
**USE 库名**
使用<br>
**CREATE TABLE 表名(字段)[注释]**
**SHOW TABLES;**
查询所有表<br>
**DESC 表名;**
查询表结构<br>
**SHOW CREATE TABLE 表名**
查看表的建表语句<br>
**ALTER TABLE 表名 ADD 字段**
添加字段<br>
**ALTER TABLE 表名 MODIFY 字段名 新类型**
修改数据类型<br>
**ALTER TABLE 表名 CHANGE 旧字段 新字段 数据类型**
修改字段名和类型<br>
**ALTER TABLE 表名 DROP 字段名**
删除字段<br>
**ALTER TABLE 表名 RENAME TO 新表名**
修改表名<br>
**DROP TABLE 表名**
删除表<br>
**TRUNCATE TABLE 表名**
删除再重创<br>
## 数据类型
| 数据类型            | 大小（字节） | 取值范围                                      | 说明                                                         |
|-------------------|------------|----------------------------------------------|--------------------------------------------------------------|
| 整数类型           |            |                                              |                                                              |
| `INT`             | 4          | -2147483648 到 2147483647                   | 常规大小整数。                                                 |
| `TINYINT`         | 1          | -128 到 127                                 | 很小的整数。                                                    |
| `SMALLINT`        | 2          | -32768 到 32767                             | 小整数。                                                       |
| `MEDIUMINT`       | 3          | -8388608 到 8388607                         | 中等大小整数。                                                 |
| `BIGINT`          | 8          | -9223372036854775808 到 9223372036854775807 | 大整数。                                                       |
| 浮点数类型          |            |                                              |                                                              |
| `FLOAT`           | 4          |                                            | 单精度浮点数。                                                 |
| `DOUBLE`          | 8          |                                            | 双精度浮点数。                                                 |
| 定点数类型          |            |                                              |                                                              |
| `DECIMAL`         |            |                                            | 带有精确小数位的定点数。                                         |
| 字符串类型          |            |                                              |                                                              |
| `CHAR`            |            |                                            | 固定长度的字符串。                                              |
| `VARCHAR`         |            |                                            | 可变长度的字符串。                                              |
| `TEXT`            |            |                                            | 较大的文本数据。                                                |
| 日期和时间类型        |            |                                              |                                                              |
| `DATE`            |            |                                            | 日期，格式为YYYY-MM-DD。                                       |
| `TIME`            |            |                                            | 时间，格式为HH:MM:SS。                                         |
| `DATETIME`        |            |                                            | 日期和时间的组合，格式为YYYY-MM-DD HH:MM:SS。                   |
| `TIMESTAMP`       |            |                                            | 自动更新的时间戳，记录插入或更新记录的时间。                     |
| 布尔类型            |            |                                              |                                                              |
| `BOOL`、`BOOLEAN` |            |                                            | 用于存储布尔值（True/False）。                                  |
| 二进制类型           |            |                                              |                                                              |
| `BINARY`          |            |                                            | 固定长度的二进制数据。                                          |
| `VARBINARY`       |            |                                            | 可变长度的二进制数据。                                          |
| 枚举类型            |            |                                              |                                                              |
| `ENUM`            |            |                                            | 用于在列表中选择一个值。                                        |

<br>

****
# DML
**INSERT INTO 表名(字段名...) VALUES(值...),(...);**
给指定字段添加数据<br>
**INSERT INTO 表名 VALUES(值...),(...);**
给全部字段添加数据<br>
**UPDATE 表名 SET 字段名1=值1,... WHERE 条件**
修改字段数据<br>
**DELETE FROM 表名 WHERE 条件**
删除数据<br>

<br>

****
# DQL
**SELECT 字段,... FROM 表名 WHERE 条件列表**
查询多个字段<br>
**SELECT 字段 AS 别名,... FROM 表名**
设置别名<br>
**SELECT DISTINCT 字段列表 FROM 表名**
去除重复记录<br><br>
**聚合函数**
| 函数      | 描述                                       |
|-----------|--------------------------------------------|
| COUNT()   | 计算行数或非NULL值的数量                    |
| SUM()     | 计算数值列的总和                            |
| AVG()     | 计算数值列的平均值                          |
| MAX()     | 找出数值列的最大值                          |
| MIN()     | 找出数值列的最小值                          |

**SELECT 聚合函数(字段列表) FROM 表名**
聚组查询<br>
**SELECT 字段列表 FROM 表名 WHERE 条件 GROUP BY 分组字段名 HAVING 分组后过滤条件**
分组查询<br>
**SELECT 字段列表 FROM 表名 ORDER BY 字段 排序方式,...**
排序查询（ASC升序 DESC降序）<br>
**SELECT 字段列表 FROM 表名 LIMIT 起始索引，查询记录数**
分页查询<br>
**DQL执行顺序**
```
FROM->WHERE->GROUP BY->HAVING->ORDER BY->LIMIT
```
<br>

****
# DCL
**USE mysql**<br>
**SELECT * FROM USER**
查看用户信息<br>
**CREATE USER ‘用户名’@'主机名' IDENTIFIED BY ‘密码’**
创建用户<br>
**ALTER USER ‘用户名’@‘主机名’ IDENTIFY WITH mysql_native_password BY '新密码'**
修改用户密码<br>
**DROP USER ‘用户名’@‘主机名’**
**SHOW GRANTS FOR ‘用户名’@‘主机名’**
查询权限<br>
**GRANT 授权列表 ON 库名.表名 TO ‘用户名’@‘主机名’**
授予权限<br>
**REVOKE 授权列表 ON 库名.表名 FROM ‘用户名’@‘主机名’**
撤销权限<br>

<br>

****
# 函数
**字符串函数**
| 函数          | 描述                           | 示例                                          |
|---------------|--------------------------------|-----------------------------------------------|
| CONCAT()      | 连接两个或多个字符串           | `SELECT CONCAT('Hello', ' ', 'World');`       |
| SUBSTRING()   | 返回字符串的子串               | `SELECT SUBSTRING('Hello World', 7, 5);`      |
| UPPER()       | 将字符串转换为大写             | `SELECT UPPER('hello');`                     |
| LOWER()       | 将字符串转换为小写             | `SELECT LOWER('WORLD');`                     |
| LENGTH()      | 返回字符串的长度               | `SELECT LENGTH('Hello');`                    |
| TRIM()        | 去除字符串两端的空格           | `SELECT TRIM('   Hello   ');`                |
| REPLACE()     | 替换字符串中的指定部分         | `SELECT REPLACE('Hello World', 'World', 'Universe');` |
| LOCATE()      | 查找字符串在另一个字符串中的位置 | `SELECT LOCATE('World', 'Hello World');`     |
<br>
**数值函数**
| 函数名称           | 函数描述                                | 示例                           |
|------------------|---------------------------------------|------------------------------|
| `ABS(x)`         | 返回一个数的绝对值。                     | `ABS(-10)` 结果为 `10`         |
| `CEILING(x)`     | 返回大于或等于给定数字的最小整数值。         | `CEILING(9.23)` 结果为 `10`    |
| `FLOOR(x)`       | 返回小于或等于给定数字的最大整数值。         | `FLOOR(9.95)` 结果为 `9`      |
| `ROUND(x [, d])` | 对一个数进行四舍五入，可指定小数位数。        | `ROUND(9.235, 2)` 结果为 `9.24` |
| `SQRT(x)`        | 返回一个数的平方根。                      | `SQRT(25)` 结果为 `5`         |
| `POWER(x, y)`    | 返回 x 的 y 次幂。                       | `POWER(2, 3)` 结果为 `8`      |
| `MOD(x, y)`      | 返回 x 除以 y 的余数。                    | `MOD(10, 3)` 结果为 `1`       |
| `SIGN(x)`        | 返回数字的正负号。                        | `SIGN(-5.5)` 结果为 `-1`      |
| `RAND([seed])`   | 返回一个随机浮点数值。                     | `RAND()` 结果为介于 0 和 1 之间的随机值 |
| `TRUNCATE(x, d)` | 截断一个数，保留指定小数位数。                | `TRUNCATE(9.999, 2)` 结果为 `9.99` |
<br>
**日期函数**
以下是MySQL中常用的日期函数以及它们的描述，使用Markdown表格语法编写：

markdown
| 函数                | 描述                                                         |
|---------------------|--------------------------------------------------------------|
| CURDATE()           | 返回当前日期（不包括时间部分）                               |
| CURRENT_DATE()      | 返回当前日期（同样不包括时间部分）                           |
| CURTIME()           | 返回当前时间（不包括日期部分）                               |
| CURRENT_TIME()      | 返回当前时间（不包括日期部分）                               |
| NOW()               | 返回当前日期和时间                                           |
| DATE()              | 提取日期或日期时间表达式的日期部分，去除时间部分             |
| TIME()              | 提取日期或日期时间表达式的时间部分，去除日期部分             |
| DAYNAME()           | 返回日期的星期几名称（例如Monday, Tuesday等）               |
| MONTHNAME()         | 返回日期的月份名称（例如January, February等）               |
| DAYOFWEEK()         | 返回日期的星期几编号（1表示星期日，2表示星期一，依此类推）  |
| DAYOFMONTH()        | 返回日期的月份中的日期编号（1到31之间的值）                 |
| DAYOFYEAR()         | 返回日期在年份中的天数编号（1到366之间的值）                |
| WEEKDAY()           | 返回日期的星期几编号（0表示星期一，1表示星期二，依此类推）  |
| YEAR()              | 返回日期的年份                                               |
| MONTH()             | 返回日期的月份                                               |
| HOUR()              | 返回时间的小时数（0到23之间的值）                           |
| MINUTE()            | 返回时间的分钟数（0到59之间的值）                           |
| SECOND()            | 返回时间的秒数（0到59之间的值）                             |
| DATE_FORMAT()       | 格式化日期或日期时间表达式为指定格式                         |
| ADDDATE() / DATE_ADD() | 在日期上增加指定的时间间隔                                 |
| SUBDATE() / DATE_SUB() | 在日期上减去指定的时间间隔                                 |
| DATEDIFF()           | 计算两个日期之间的天数差                                   |
| TIMEDIFF()           | 计算两个时间之间的时间差                                   |
<br>
**流程控制函数**
| 函数               | 描述                                                            |
|---------------------|-----------------------------------------------------------------|
| IF()                | 如果条件为真，则返回一个值；否则返回另一个值                   |
| IFNULL()            | 如果表达式为NULL，则返回替代值，否则返回表达式本身             |
| CASE                | 类似于switch语句，在满足条件时返回一个值或执行一系列操作      |
| COALESCE()          | 返回参数列表中的第一个非NULL值                                 |
| NULLIF()            | 如果两个表达式相等，则返回NULL；否则返回第一个表达式的值       |
<br>