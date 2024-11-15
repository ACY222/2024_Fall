class TrieTreeNode:
    def __init__(self):
        self.children = {}
        self.count = 0

class TrieTree:
    def __init__(self):
        self.root = TrieTreeNode()

    def insert(self, word):
        node = self.root
        for letter in word:
            if letter not in node.children:
                node.children[letter] = TrieTreeNode()
            node = node.children[letter]
        node.count += 1
    
def match(trie_tree, text_len, text):
    count = 0

    for start in range(text_len):
        node = trie_tree.root 
        for next in range(start, text_len):
            if text[next] in node.children:
                node = node.children[text[next]]
                count += node.count
            else:
                break
    return count

if __name__ == "__main__":
    trie_tree = TrieTree()
    word_num, text_len = map(int, input().split())
    words = []
    for i in range(1, word_num + 1):
        len, word = input().split() # len is of no use
        words.append(word)
        trie_tree.insert(word)
    text = input().strip()

    count = match(trie_tree, text_len, text)
    print(count)
    
