class DisjointSet
{
    private:
        vector<int> parent;
        vector<int> size;
    public:
        DisjointSet(int n)
        {
            parent.resize(n);
            size.resize(n);
            for(int i=0;i<n;i++)
            {
                parent[i] = i;
                size[i] = 1;
            }
        }
        int findUParent(int n)
        {
            if(parent[n] == n)return n;
            return (parent[n] = findUParent(parent[n]));
        }
        void unionn(int u,int v)
        {
            int pu = findUParent(u);
            int pv = findUParent(v);
            if(pu == pv)return;
            
            if(size[pu]>size[pv])
            {
                parent[pv] = pu;
                size[pu]+=size[pv];
            }
            else if(size[pv]>=size[pu]) 
            {
                parent[pu] = pv;
                size[pv]+=size[pu] ;
            }
        }
};