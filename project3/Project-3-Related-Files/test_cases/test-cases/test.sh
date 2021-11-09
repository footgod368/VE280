./p3 > output/0.out
./p3 species world_test/error-test/out_of_bound_world 10 > output/1.out
./p3 species world_test/error-test/overlap_world 2 > output/2.out
./p3 species world_test/complex/world8 -1 > output/3.out
./p3 species world_test/error-test/too_large_height_world 2 > output/4.out
./p3 species world_test/error-test/too_large_width_world 2 > output/5.out
./p3 species world_test/error-test/too_many_world 10 > output/6.out
./p3 species_test/long_prog_species world_test/complex/world8 2 > output/7.out
./p3 species_test/too_many_species world_test/complex/world8 2 > output/8.out
./p3 species world_test/error-test/unknown_direction_world 10 > output/9.out
./p3 species_test/bad_instr_species world_test/complex/world8 2 > output/10.out
./p3 species world_test/error-test/unknown_species_world  10 > output/11.out
./p3 species world_test/error-test/zero_height_world 10 > output/12.out
./p3 species world_test/error-test/zero_width_world 10 > output/13.out
./p3 species_test/species world_test/complex/world4 10 v > output/14.out
./p3 species_test/species world_test/complex/world4 10 > output/15.out
./p3 species_test/species world_test/complex/world8 50 verbose > output/16.out
./p3 species_test/species world_test/complex/world8 20 > output/17.out
./p3 species_test/species world_test/right/right 10 v > output/18.out
./p3 species_test/species world_test/empty/path_finder 20 v > output/19.out
./p3 species_test/species world_test/enemy/enemy_enemy 10 v > output/20.out
./p3 species_test/species world_test/enemy/enemy_same 10 > output/21.out
./p3 species_test/species world_test/error-test/neg_height_world 10 v > output/22.out
./p3 species_test/species world_test/error-test/neg_width_world 10 v > output/23.out
./p3 species_test/species world_test/error-test/too_many_world 10 v > output/24.out
./p3 species_test/species world_test/error-test/zero_height_world 10 v > output/25.out
./p3 species_test/species world_test/error-test/zero_width_world 10 v > output/26.out
./p3 species_test/species world_test/hop/hop_block 10 v > output/27.out
./p3 species_test/species world_test/hop/hop_down 10 v > output/28.out
./p3 species_test/species world_test/hop/hop_up 10 v > output/29.out
./p3 species_test/species world_test/infect/hop_flytrap 10 v > output/30.out
./p3 species_test/species world_test/left/left 10 v > output/31.out
./p3 species_test/species world_test/same/same_same 10 v > output/32.out
./p3 species_test/species world_test/same/same_wall 10 v > output/33.out
./p3 species_test/species world_test/wall/wall_turner 10 v > output/34.out

for ((i=1;i<=34;i++))
do
    diff output/$i.out stdOutput/$i.out
done