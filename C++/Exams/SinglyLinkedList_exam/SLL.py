

class SLL:
    __slots__ = ['value', 'next', 'head', 'tail']

    def __init__(self):
        self.value = list()
        self.next = list()


    def is_empty(self):
        return len(self.next) == 0

    def prepend(self, element):
        
        if self.is_empty():
            
            self.next.append(-1)

            self.value.append(element)

            self.head = self.value[0]
            self.tail = self.value[0]

        else:
            temp = []
            temp.append(len(self.value) - 1)

            for x in self.next:
                temp.append(x)

            self.next = temp

            temp = []
            temp.append(element)

            for x in self.value:
                temp.append(x)
            
            self.value = temp

            self.head = self.value[0]


    def append(self, element):
        
        if self.is_empty():
                      
            self.next.append(-1)

            self.value.append(element)

            self.head = self.value[0]
            self.tail = self.value[0]

        else:

            self.next.append(len(self.value) - 1)

            self.value.append(element)

            self.tail = element


    def remove_from_head(self):
        indeks = self.value.index(self.head)
        self.value.remove(self.head)
        self.next.pop([indeks])


    def remove_from_tail(self):
        indeks = self.value.index(self.tail)
        self.value.remove(self.tail)
        self.next.pop([indeks])

    def remove(self, index):
        pass

    def __str__(self):

        for x in range(0, len(self.value)):
            print("Node with value " + str(self.value[x]) + " and neighbor at index " + str(self.next[x]))

        return ""
    
    __repr__ = __str__
        


if __name__ == "__main__":
    
    lista = SLL()
    lista.prepend(5)
    lista.prepend(8)
    lista.append(9)
    lista.prepend(12)
    lista.prepend(24)
    lista.append(3)
    lista.prepend(1)

    print(lista)

    lista.remove(3)

    print(lista)

