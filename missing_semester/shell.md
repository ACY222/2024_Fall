

foo=bar         store the string "bar" in the register, space matters in shell

echo "Value is $foo"        ->  Value is bar
echo 'Value is $foo'        ->  Value is $foo

!!          repeat last command

$?          the error code of last command

$_          the last argument of last command 


if-else:
* command 1 || command 2        if command 1 is true, over. Otherwise it will 
  run command 2
* command 1 && command 2        if command 1 is false, over
* 