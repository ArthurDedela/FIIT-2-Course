#ifndef _HEROFACTORY
#define _HEROFACTORY


const vector<string> HeroNames = {
    "Knight",
    "Archer",
    "Wizard"
};

template<typename T> shared_ptr<Hero> create() {
    return make_shared<T>();
}

class HeroFactory {
private:
    using mapVal = shared_ptr<Hero>(*)();
    map<string, mapVal> factory;

public:
    HeroFactory() {
        factory["Knight"] = create<Knight>;
        factory["Archer"] = create<Archer>;
        factory["Wizard"] = create<Wizard>;
    }

    shared_ptr<Hero> createHero(const string & name) {
        return factory[name]();
    }
};


#endif // !_HEROFACTORY