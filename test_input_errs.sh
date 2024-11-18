
echo -e "\nmissing komma"
./test_parsing ./maps/invalid/rgb/missing_komma.cub
echo -e "\n\nneg number"
./test_parsing ./maps/invalid/rgb/neg_number.cub
echo -e "\n\ntoo big number"
./test_parsing ./maps/invalid/rgb/too_big_number.cub
echo -e "\n\ninvalid char"
./test_parsing ./maps/invalid/rgb/invalid_char.cub

echo -e "\n\nmissing_NO"
./test_parsing maps/invalid/missing_elements/missing_NO.cub
echo -e "\n\nmissing_SO"
./test_parsing maps/invalid/missing_elements/missing_SO.cub
echo -e "\n\nmissing_WE"
./test_parsing maps/invalid/missing_elements/missing_WE.cub
echo -e "\n\nmissing_EA"
./test_parsing maps/invalid/missing_elements/missing_EA.cub
echo -e "\n\nmissing_C"
./test_parsing maps/invalid/missing_elements/missing_C.cub
echo -e "\n\nmissing_F"
./test_parsing maps/invalid/missing_elements/missing_F.cub
echo -e "\n\nmissing_F_NO"
./test_parsing maps/invalid/missing_elements/missing_F_NO.cub
echo -e "\n\nmissing_MAP"
./test_parsing maps/invalid/missing_elements/missing_map.cub

echo -e "\n\ninvalid_map_char"
./test_parsing maps/invalid/invalid_maps/invalid_map_char.cub
echo -e "\n\ninvalid_chars_after_map"
./test_parsing maps/invalid/invalid_maps/invalid_chars_after_map.cub
