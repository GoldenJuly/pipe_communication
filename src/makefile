bin_path:=../bin
bin_demo1:=$(bin_path)/test_demo1
bin_demo2:=$(bin_path)/test_demo2
bin_demo3:=$(bin_path)/test_demo3
bins:=$(bin_demo1) $(bin_demo2) $(bin_demo3)

all: $(bins)
$(bin_demo1): ./test_demo1.cpp
	g++ -o $@ $^
$(bin_demo2): ./test_demo2.cpp
	g++ -o $@ $^
$(bin_demo3): ./test_demo3.cpp
	g++ -o $@ $^

clean:
	rm -rf $(bins)

run:
	@echo "------------------------"
	$(bin_demo1)
	@echo ""
	@echo "------------------------"
	$(bin_demo2)
	@echo ""
	@echo "------------------------"
	$(bin_demo3)