echo starting cycle 1
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.1
tail -1000 1.24.log > 1.24.log.1
tail -1000 infinite.log > infinite.log.1

echo starting cycle 2
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.2
tail -1000 1.24.log > 1.24.log.2
tail -1000 infinite.log > infinite.log.2

echo starting cycle 3
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.3
tail -1000 1.24.log > 1.24.log.3
tail -1000 infinite.log > infinite.log.3

echo starting cycle 4
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.4
tail -1000 1.24.log > 1.24.log.4
tail -1000 infinite.log > infinite.log.4

echo starting cycle 5
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.5
tail -1000 1.24.log > 1.24.log.5
tail -1000 infinite.log > infinite.log.5

echo starting cycle 6
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.6
tail -1000 1.24.log > 1.24.log.6
tail -1000 infinite.log > infinite.log.6

echo starting cycle 7
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.7
tail -1000 1.24.log > 1.24.log.7
tail -1000 infinite.log > infinite.log.7

echo starting cycle 8
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.8
tail -1000 1.24.log > 1.24.log.8
tail -1000 infinite.log > infinite.log.8

echo starting cycle 9
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.9
tail -1000 1.24.log > 1.24.log.9
tail -1000 infinite.log > infinite.log.9

echo starting cycle 10
sleep 60
./test_cfdp < test.infinite | tee infinite.log
tail -1000 23.log > 23.log.10
tail -1000 1.24.log > 1.24.log.10
tail -1000 infinite.log > infinite.log.10

echo "Woh.  Failed 10 times!"



