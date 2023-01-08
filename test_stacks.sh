make stack
rm ft_stack_test_outuput stack_test_output

echo "************* ft_stack times **************"
time ./ft_stack_test >> ft_stack_test_output
echo""
echo""
echo "*************** stack times ***************"
time ./stack_test >> stack_test_output
echo""
echo""
echo "******************* diff *******************"

diff ft_stack_test_output stack_test_output
make fclean