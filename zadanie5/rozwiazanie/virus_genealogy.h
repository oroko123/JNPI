#ifndef VIRUS_GENEALOGY_H
#define VIRUS_GENEALOGY_H

#include <map>
#include <set>
#include <vector>
#include <memory>

class VirusNotFound : public std::exception {
    virtual const char *what() const noexcept {
        return "VirusNotFound";
    }
};

class VirusAlreadyCreated : public std::exception {
    virtual const char *what() const noexcept {
        return "VirusAlreadyCreated";
    }
};

class TriedToRemoveStemVirus : public std::exception {
    virtual const char *what() const noexcept {
        return "TriedToRemoveStemVirus";
    }
};

template<class Virus>
class VirusGenealogy {
private:
    typedef typename Virus::id_type id_type;

    class VirusHolder {
    public:
        std::shared_ptr<Virus> virus;
        std::set<id_type> parents;
        std::set<id_type> children;

        /// Standard says that in case of exception,
        /// destructors of attributes will be called
        VirusHolder(id_type const &_id, std::vector<id_type> const &_parents) {
            this->virus = std::shared_ptr<Virus>(new Virus(_id));
            this->parents = std::set<id_type>(_parents.begin(), _parents.end());
        }

        VirusHolder(id_type const &_id) {
            VirusHolder(_id, std::vector<id_type>());
        }

        VirusHolder() { }
    };

    std::map<id_type, VirusHolder> genealogy;
    id_type stem_id;


    /// strong
    /// [why]: operator [i] is strong
    void create_stem(id_type const &id) {
        genealogy[id] = VirusHolder(id);
    }


public:

    /// Standard says that in case of exception,
    /// destructors of attributes will be called
    VirusGenealogy(id_type const &_stem_id) {
        create_stem(_stem_id);
        stem_id = _stem_id;
    }

    VirusGenealogy(const VirusGenealogy &) = delete;

    VirusGenealogy &operator=(const VirusGenealogy &) = delete;

    VirusGenealogy &operator=(VirusGenealogy &&) = delete;

    /// no-throw
    /// [why]: returns a private attribute
    id_type get_stem_id() const noexcept {
        return stem_id;
    }

    /// strong
    /// [why]: method find is strong
    bool exists(id_type const &id) const {
        return genealogy.find(id) != genealogy.end();
    }


    /// strong
    /// [why]: method find is strong
    Virus &operator[](id_type const &id) const {
        if (!exists(id)) {
            throw VirusNotFound();
        }
        return *genealogy.find(id)->second.virus;
    }

    /// strong
    /// [why]: method find is strong
    std::vector<id_type> get_children(id_type const &id) const {
        if (!exists(id)) {
            throw VirusNotFound();
        }
        return std::vector<id_type>
                (genealogy.find(id)->second.children.begin(),
                 genealogy.find(id)->second.children.end());
    }

    /// strong
    /// [why]: method find is strong
    std::vector<id_type> get_parents(id_type const &id) const {
        if (!exists(id)) {
            throw VirusNotFound();
        }
        return std::vector<id_type>
                (genealogy.find(id)->second.parents.begin(),
                 genealogy.find(id)->second.parents.end());
    }

    /// strong
    /// [why]: second method create is strong
    void create(id_type const &id, id_type const &parent_id) {
        create(id, std::vector<id_type> {parent_id});
    }

    /// strong
    /// [why]: insert is strong, we delete all put edges
    void create(id_type const &id, std::vector<id_type> const &parent_ids) {
        if (exists(id)) {
            throw VirusAlreadyCreated();
        }
        if (parent_ids.empty()) {
            throw VirusNotFound();
        }
        for (id_type parent_id : parent_ids) {
            if (!exists(parent_id)) {
                throw VirusNotFound();
            }
        }

        std::vector<std::pair<typename std::map<id_type, VirusHolder>::iterator,
                typename std::set<id_type>::iterator> > v;
        try {
            for (id_type parent : parent_ids) {
                auto parent_it = genealogy.find(parent);
                auto el_it = parent_it->second.children.insert(id).first;
                v.push_back(make_pair(parent_it, el_it));
            }

            genealogy.emplace(id, VirusHolder(id, parent_ids));

        } catch (...) {
            for (size_t i = 0; i < v.size(); i++) {
                /// erase(iterator) is no-throw
                (v[i].first)->second.children.erase(v[i].second);
            }
            throw;
        }
    }

    /// strong
    /// [why]: exists, find are strong. If exception occurs in adding second edge,
    /// we delete the first one.
    void connect(id_type const &child_id, id_type const &parent_id) {
        if (!exists(child_id) || !exists(parent_id)) {
            throw VirusNotFound();
        }

        auto child_it = genealogy.find(child_id);
        auto it = child_it->second.parents.insert(parent_id).first;
        try {
            genealogy[parent_id].children.insert(child_id);
        } catch (...) {
            ///erase with iterator parameter is no-throw
            child_it->second.parents.erase(it);
            throw;
        }
    }

    /// That doesn't work yet.
    void remove(id_type const &id) {
        if (!exists(id)) {
            throw VirusNotFound();
        }
        if (get_stem_id() == id) {
            throw TriedToRemoveStemVirus();
        }
        auto it = genealogy.find(id);
        
        for (id_type parent_id : it->second.parents) {
            genealogy[parent_id].children.erase(id);
        }

        for (id_type child_id : it->second.children) {

            genealogy[child_id].parents.erase(id);
            if (genealogy[child_id].parents.empty()) {
                remove(child_id);
            }
        }
        genealogy.erase(it);
    }
};

#endif //VIRUS_GENEALOGY_H
