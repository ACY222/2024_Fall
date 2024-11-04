# Answer

PB22111620 艾昶

## 正则表达式

* 根据该表达式中的 `@` 和 `.`（尤其是 `@`），我认为它很有可能是邮箱账号，它也的确能够匹配我的三个邮箱账号。但它还能匹配含有 `-`, `+` 的字符串，我所用的几个邮箱似乎并不支持这样的账号（比如 `gmail` 只允许 `.`），不过也可能是某些我没用过的邮箱支持这个格式。

## Flex

* 第三条规则被触发，即识别出来 `+=`。`flex info` 的 `matching` 部分提到 `If it finds more than one match, it takes the one matching the most text (for trailing context rules, this includes the length of the trailing part, even though it will then be returned to the input).`——第三条规则识别出的文本最长，故选择第三条。
* 第一条规则被触发。`flex info` 中 `matching` 部分提到 `If it finds two or more matches of the same length, the rule listed first in the 'flex' input file is chosen.`——通过1、2两条规则识别出来长度相同的两个匹配，此时选择先列出来的规则。
* 仍然是第一条，原因同上。
实际上，在答题之前我只尝试编写了第一题的程序，后两道题完成后才尝试编程去验证我的答案，发现 2 的结果是正确的，但对于 3，在 `flex wc.l` 时报错：`wc.1:18: warning, rule cannot be matched`，——即以该顺序编写规则，所有正则表达式均不可能被识别为 `ABC`，所以 `flex` 认为代码写的有问题。

## bison

* 自底向上分析不受左递归影响
* 可包含头文件 `stdlib.h` 后将 `calc.y: 45-56` 修改为
```
term
: factor
{
    $$ = $1;
}
| term MULOP factor
{
    switch ($2) {
        case '*': $$ = $1 * $3; break;
        case '/': {
            if($3 == 0){
                yyerror("Divisor mustn't be 0!"); exit(1);
            }
            else{
                $$ = $1 / $3; break;
            }
        }
    }
}
```
