import numpy as np

class DisjointSet:
    def __init__(self, elems):
        self.elems_ = elems

    def find(self, elem):
        if self.elems_[elem] < 0:
            return elem
        root = self.find(self.elems_.at(elem))
        self.elems_[elem] = root
        return root

    def setunion(self, a, b):
        if a == b or a >= self.elems_.size or b >= self.elems_.size:
            return None
        
        left = self.find(a)
        right = self.find(b)

        if left == right:
            return None
        
        if self.size(a) >= self.size(b):
            size = self.size(b)

            self.elems_[right] = left
            self.elems_[left] -= size
        else:
            size = self.size(a)

            self.elems_[left] = right
            self.elems_[right] -= size
    
    def size(self, elem):
        return -1 * self.elems_[self.find(elem)]
    
    def getValue(self, elem):
        return self.elems_[elem]
        

#convert to union by size uptree

