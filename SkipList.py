import random
MAX_DEPTH = 5


class SkipNode:
    def __init__(self, height=0, elem=None):
        self.elem = elem
        # 第一层next、第二层next，以此类推
        self.next = [None] * height

    def __repr__(self):
        return str(self.elem)


class SkipList:
    def __init__(self):
        # 大节点，包含了几行跳跃表的head
        self.head = SkipNode()

    # 改变节点而引发的更新操作
    # update :list 记录着elem在每行应该插入的位置
    def update_list(self, elem):
        update = [None] * len(self.head.next)
        x = self.head
        for i in reversed(range(len(self.head.next))):
            while x.next[i] is not None and x.next[i].elem < elem:
                x = x.next[i]
            update[i] = x
        return update

    # 查找elem 是否在跳跃表中
    def find(self, elem, update=None):
        if update is None:
            update = self.update_list(elem)
        if len(update) > 0:
            # 找到
            candidate = update[0].next[0]
            if candidate is not None and candidate.elem == elem:
                return candidate
        # 找无
        return None

    # 插入元素至跳跃表
    def insert(self, elem):
        node = SkipNode(self.random_height(), elem)
        while len(self.head.next) < len(node.next):
            self.head.next.append(None)
        # 寻找每行应该插入的位置
        update = self.update_list(elem)
        if self.find(elem, update) is None:
            for i in range(len(node.next)):
                node.next[i] = update[i].next[i]
                update[i].next[i] = node

    # 给元素随机分配高度
    def random_height(self):
        k = 1
        while random.randint(0, 1):
            k = k + 1
            if k == MAX_DEPTH:
                break
        return k

    # 在跳跃表中移除元素
    def remove(self, elem):
        update = self.update_list(elem)
        x = self.find(elem, update)
        if x is not None:
            for i in range(len(x.next)):
                update[i].next[i] = x.next[i]
                if self.head.next[i] is None:
                    self.head.next = self.head.next[:i]
                    return

    # 自上而下遍历跳跃表
    def traversal(self):
        for i in reversed(range(len(self.head.next))):
            x = self.head
            line = []
            while x.next[i] is not None:
                line.append(str(x.next[i].elem))
                x = x.next[i]
            print('line{}: '.format(i + 1) + '->'.join(line))


if __name__ == '__main__':
    skp = SkipList()

    # 测试插入
    ramnum = [random.randint(0, 49999) for _ in range(0, 50)]
    for num in ramnum:
        skp.insert(num)
    skp.traversal()

    # 测试查找
    print("want to  find: ", end='')
    tg = int(input())
    print(skp.find(tg))

    print("want to  find: ", end='')
    tg = int(input())
    print(skp.find(tg))

    # 测试删除
    print("want to  remove: ", end='')
    tg = int(input())
    skp.remove(tg)
    skp.traversal()

    print("want to  find: ", end='')
    tg = int(input())
    print(skp.find(tg))

    print("want to  remove: ", end='')
    tg = int(input())
    skp.remove(tg)
    skp.traversal()

    print("want to  find: ", end='')
    tg = int(input())
    print(skp.find(tg))

