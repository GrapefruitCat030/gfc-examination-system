#pragma once 

class IDataBaseRepository {
public:
    virtual void CreateItem() = 0;
    virtual void FindItem() = 0;
    virtual void UpdateItem() = 0;
    virtual void DeleteItem() = 0;
};

// 实现具体的数据库访问逻辑
class JsonDBRepository : public IDataBaseRepository {
public:
    void CreateItem() override {
        // 在JSON存储中创建用户的逻辑
    }

    void FindItem() override {
        // 在JSON存储中查找用户的逻辑
    }

    void UpdateItem() override {
        // 在JSON存储中更新用户的逻辑
    }

    void DeleteItem() override {
        // 在JSON存储中删除用户的逻辑
    }
};

class RedisDBRepository : public IDataBaseRepository {
public:
    void CreateItem() override {
        // 在Redis存储中创建用户的逻辑
    }

    void FindItem() override {
        // 在Redis存储中查找用户的逻辑
    }

    void UpdateItem() override {
        // 在Redis存储中更新用户的逻辑
    }

    void DeleteItem() override {
        // 在Redis存储中删除用户的逻辑
    }
};
