1. `s`: delete the current character and then insert = `x` + `i` 
2. `*`: move to the next same word in the chapter
    `#`: move to the last same word in the chapter
3. `aw, as, ap`: a word, a sentence, a paragraph
4. `g + ~/u/U`: flip the case / change to lower/upper case
5. `gc`: change the comment state
6. `C-o`: insert-normal mode->allow you to excute a command in normal mode
when you are in insetion mode. Very powerful, right?
7. `C-o`+`=<expression>`+`<CR>`: a computer
8. in visual mode
    - `o` : 切换选区的活动端
    - `gv`: 重选上次的高亮选区
9. 命令行模式
    - some notations
        | symbols | address |
        | :-----: | :-----: |
        |  `.`    | current line  |
        |  `0`    | the virtual line above the first line |
        | `<num>` | the <num>-th line |
        | `$`     | last line | 
        | `%`     | the whole file | 
        | `'<`    | 上次高亮选区的起始行 |
        | `'>`    | 上次高亮选区的结束行 |
        | `'<,'>` | 上次高亮选区的范围 |
    - 用地址指定范围
        - `:{start}, {end}`: use two address to specify a range
    - 用高亮选区指定范围
    - 用模式指定范围
    - 用偏移对地址进行修正
        - `:{start} + offset1, {end} + offset2`
10. <C-f> <C-b>翻页, <C-d>, <C-u> 翻半页
11. "d + i + {", delete (contents) inner {}
12. `:noh`: no highlight, used after search
