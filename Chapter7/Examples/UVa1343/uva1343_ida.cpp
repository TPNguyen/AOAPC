// BFS on 1,2,3 is too slow causing TLE. This is b/c hash size can increase upto C(24, 8) = 735471 before
// we get to a solution. And even when we reach the final solution, we have to check other numbers and conclude
// no other number can reach better (shorter) paths.
// IDA* to the rescure. This method combines the benefits of both BFS and DFS: the effective order of
// traversal is the same as BFS so the solution is guaranteed to be the shortest path. DFS's advantage
// include smaller memory footprint, no need to set aside memory for father, vis, dist ... (meta info) that
// are needed in BFS to track the solution. (of course, you can add vis hash to determin if a state with
// a larger depth has previously been visited and if yes, you can update the depth and continue)
// A* provides the way for backtracking by using hint function.
// Ref:
// https://github.com/aoapc-book/aoapc-bac2nd/blob/master/ch7/UVa1343.cpp
// http://morris821028.github.io/2015/03/08/uva-1343/ (best in my opinion since it updates the max depth non-incrementally--- faster code)
// http://blog.csdn.net/the___best/article/details/48209795
// http://blog.csdn.net/acm_hkbu/article/details/42489903
// http://m.blog.csdn.net/blog/XDU_PYL/45874325
// http://www.xlgps.com/article/13166.html
// http://www.cnblogs.com/Bowen-/p/4955782.html
//
