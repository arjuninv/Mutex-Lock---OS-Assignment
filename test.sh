rm -f results.txt
gcc output.o < tests/input1.txt 2> tests/output_latest.txt
cmp tests/output1.txt tests/output_latest.txt
RESULT=$?
if [ $RESULT -eq 0 ]; then
	echo "Test 1: Passed" >> results.txt
else
	echo "Test 1: Failed" >> results.txt
fi