make map
rm ft_map_test_output map_test_output

echo "************* ft_map times **************"
time ./ft_map_test >> ft_map_test_output
echo""
echo""
echo "*************** map times ***************"
time ./map_test >> map_test_output
echo""
echo""
echo "******************* diff *******************"

diff ft_map_test_output map_test_output
make fclean