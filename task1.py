"""@Author: Jianquan Li(25924710) @Title: Task 1 @Description: About find a specific type of eulerian circult 
@Comment: some codes found online (url: "http://codegists.com/snippet/python/hierholzerpy_jdelafon_python") are 
modified and applied in the program below, and with fully understanding. """


def permutation(string, prefix, n, a):  # Using recursion to get all the vertices
    if len(prefix) == n:
        a.append(prefix)
    else:
        for i in range(len(string)):
            permutation(string, prefix + string[i], n, a)


V = []  # create the Vertex list
m = int(input("Please enter the value of m([2,5]): "))
n = int(input("Please enter the value of n([2,3]): "))
string = "ABCDE"[0:m]  # the range of alphabet
permutation(string, "", n, V)

adj_list = []  # contains all the edges
for i in V:
    for o in V:
        if i != o and i[len(i) - 2:] == o[0:len(o) - 1]:
            adj_list.append((i, o))


def outgoing(vertex, edges):
    return [edge for edge in edges if edge[0] == vertex]  # outgoing edges


def find_a_circuit(source, edges):
    path = [source]  # add source to the path
    adj = outgoing(source, edges)
    while adj:
        e = adj[0]
        edges.remove(e)
        path.append(e[1])
        source = e[1]
        adj = outgoing(source, edges)
    return path, edges


def hierholzer(vertices, edges):
    source = vertices[0]  # random pick the first as a source node
    circuit, edges = find_a_circuit(source, edges)  # run the first iteration
    unvisited = set(circuit)
    while len(unvisited) != 0:
        source = unvisited.pop()
        if len(outgoing(source, edges)) != 0:
            i = circuit.index(source)
            sub, E = find_a_circuit(source, edges)
            circuit = circuit[:i] + sub[:-1] + circuit[i:]
            unvisited.update(sub)

    return circuit


Eulerian_path = hierholzer(V, adj_list)
finalised = Eulerian_path[0]
for i in range(1, len(Eulerian_path) - 1):
    finalised = finalised + Eulerian_path[i][len(Eulerian_path[i]) - 1]
file = open("outputTask1.txt", "w")
file.write(finalised)
file.close()
