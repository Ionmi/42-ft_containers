make vector
rm ft_vector_test_output vector_test_output

echo "************* ft_vector times **************"
time ./ft_vector_test >> ft_vector_test_output
echo""
echo""
echo "*************** vector times ***************"
time ./vector_test >> vector_test_output
echo""
echo""
echo "******************* diff *******************"

diff ft_vector_test_output vector_test_output
make fclean