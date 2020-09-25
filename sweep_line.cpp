struct event {
	ll x, t, i;
	bool operator<(const event &o) const {
		return make_pair(x, t)<make_pair(o.x, o.t);
	}
};

vector<event> vec;
cin>>l>>r;
struct event ev;
ev.x = l;
ev.t = 1;
ev.i = i;
struct event ev2;
ev2.x = r;
ev2.t = 2;
ev2.i = i;
vec.pb(ev);
vec.pb(ev2);

sort(all(vec));

set<int> s;
for(auto ev : vec)
{
    if(ev.t==1) s.insert(ev.i);
    else s.erase(ev.i);
}
