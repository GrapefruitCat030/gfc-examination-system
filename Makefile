# 编译器设置
CXX = g++
CXXFLAGS = -std=c++2a -Wall -g3

# 源文件和头文件路径
SRC_DIR = src
INC_DIR = include

# 获取所有源文件和对应的目标文件
SRCS = $(wildcard $(SRC_DIR)/*.cc)
OBJS = $(patsubst $(SRC_DIR)/%.cc, %.o, $(SRCS))

# 可执行文件名
TARGET = exam_system

# 默认目标
all: $(TARGET)

# 生成可执行文件
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 生成目标文件
%.o: $(SRC_DIR)/%.cc
	$(CXX) $(CXXFLAGS) -I $(INC_DIR) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)