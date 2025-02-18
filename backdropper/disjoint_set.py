import numpy as np

class DisjointSet:
    def __init__(self, elems):
        self.elems_ = np.full(elems, -1)
    
    def find(self, elem):
        if self.elems_[elem] < 0:
            return elem
        root = self.find(self.elems_[elem])
        self.elems_[elem] = root
        return root

    def setunion(self, a, b):
        if a == b or a >= len(self.elems_) or b >= len(self.elems_):
            return None
        
        left = self.find(a)
        right = self.find(b)

        if left == right:
            return None
        
        if self.size(left) >= self.size(right):
            self.elems_[left] += self.elems_[right]
            self.elems_[right] = left
        else:
            self.elems_[right] += self.elems_[left]
            self.elems_[left] = right
    
    def size(self, elem):
        return -self.elems_[self.find(elem)]
    
    def getValue(self, elem):
        return self.elems_[elem]
