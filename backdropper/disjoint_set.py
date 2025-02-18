import numpy as np

class DisjointSet:
    def __init__(self, elems):
        self.elems_ = np.full(elems, -1)  # Initialize each element as its own set
    
    def find(self, elem):
        if self.elems_[elem] < 0:
            return elem
        root = self.find(self.elems_[elem])  # Path compression
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
            self.elems_[right] = left
            self.elems_[left] -= self.size(right)
        else:
            self.elems_[left] = right
            self.elems_[right] -= self.size(left)
    
    def size(self, elem):
        return -self.elems_[self.find(elem)]
    
    def getValue(self, elem):
        return self.elems_[elem]
