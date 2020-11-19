**Setup:**
1) Install lcurl: sudo apt install curl
2) Install lcurlpp: sudo apt install libcurlpp-dev
3) Install ljsoncpp: sudo apt install libjsoncpp-dev
4) Make sure http://ked.informatik.uni-bremen.de:8090/k4r-core/api/v0/stores/21 is online

**Compile:**
1) Open Terminal
2) g++ Entity.cpp -o Entity -lcurl -lcurlpp -ljsoncpp 

**Run:**
1) ./Entity 
