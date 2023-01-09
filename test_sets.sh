make set
rm ft_set_test_output set_test_output

echo "************* ft_set times **************"
time ./ft_set_test >> ft_set_test_output
echo""
echo""
echo "*************** set times ***************"
time ./set_test >> set_test_output
echo""
echo""
echo "******************* diff *******************"

diff ft_set_test_output set_test_output
make fclean