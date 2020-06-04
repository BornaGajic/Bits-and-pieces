class CSLL:
    __slots__ = ['value', 'next', 'head']

    def __init__(self):
       self.value = list()
       self.next = list()
       self.head = 0

    def is_empty(self):
        return self.value.count == 0

    def prepend(self, element):
        if not self.is_empty():

            temp1 = list()
            temp2 = list()

            temp1.append(element)

            for x in self.value:
                temp1.append(x)
            
            self.value = temp1

            temp2.append(self.head)
            for y in self.next:
                temp2.append(y)
            
            self.next = temp2

            self.head = self.head + 1

    def append(self, element):
        if not self.is_empty():

            self.value.append(element)

            self.next.append(self.head)

            self.head = self.head + 1
            

    def remove(self, index):
        self.value.remove(self.value[index])


    def prev(self, index):
         return self.value[index - 1]

    def __str__(self):

        for x in range(0, len(self.value)):
            print("Node with value " + str(self.value[x]) + " and neighbor at index " + str(self.next[x]))

        return ""
    __repr__ = __str__


lista = CSLL()


lista.append(1)
lista.append(2)
lista.append(3)
lista.prepend(4)

print(lista)