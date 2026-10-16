#include <algorithm>
#include <iostream>
#include <memory>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

class llama
{
    public:
        enum class sex: bool { MALE, FEMALE };
        static const std::shared_ptr<llama> noname;

    private:
        std::string name;
        sex gender;
        std::shared_ptr<llama> father;
        std::shared_ptr<llama> mother;
        std::vector<std::weak_ptr<llama>> children;

    public:
        llama(const std::string& name, sex s,
              std::shared_ptr<llama> father = nullptr,
              std::shared_ptr<llama> mother = nullptr) :
              name(name), gender(s),
              father(father ? father : noname),
              mother(mother ? mother : noname),
              children(std::vector<std::weak_ptr<llama>>())

        {
            std::cout << "Powstała lama " << name << "!\n";
        }

        ~llama()
        {
            std::cout << "Lama " << name <<  " zniszczona!\n";
        }

        const std::string& getName() const
        {
            return this->name;
        }

        const std::shared_ptr<llama>& getFather() const
        {
            return father;
        }

        const std::shared_ptr<llama>& getMother() const
        {
            return mother;
        }

        sex getGender() const
        {
            return gender;
        }

        const std::vector<std::weak_ptr<llama>>& getChildren() const
        {
            return children;
        }

        void addChild(const std::weak_ptr<llama>& l)
        {
            std::cout << name << " ma nowe młode.\n";
            children.push_back(l);
        }

        void removeChild(const std::weak_ptr<llama>& l)
        {
            const std::shared_ptr<llama> target = l.lock();
            if (!target)
                throw std::logic_error("Nie można usunąć wygasłego dziecka!");

            auto childToDelete = std::find_if(
                children.cbegin(), children.cend(),
                [&target](const std::weak_ptr<llama>& child) {
                    return child.lock() == target;
                }
            );

            if (childToDelete == children.cend())
                throw std::logic_error("Lama " + target->getName() +
                    " nie jest dzieckiem lamy " + getName() + "!");

            children.erase(childToDelete);
        }
};

const std::shared_ptr<llama> llama::noname =
    std::make_shared<llama>("noname", llama::sex::MALE, nullptr, nullptr);

class herd
{
    private:
        std::set<std::shared_ptr<llama>> members;

    public:
        bool isNameInHerd(const std::string& name) const
        {
            return std::any_of(members.begin(), members.end(),
                [&name](const std::shared_ptr<llama>& l) {
                    return l->getName() == name;
                }
            );
        }

        void birthLlama(const std::shared_ptr<llama>& l)
        {
            std::shared_ptr<llama> father = l->getFather();
            std::shared_ptr<llama> mother = l->getMother();

            if (isNameInHerd(l->getName()))
                throw std::logic_error(
                    "Lama o takim imieniu już jest w stadzie!");

            if (mother == llama::noname || !isNameInHerd(mother->getName()))
                throw std::logic_error(
                    "Matka urodzonej lamy musi należeć do stada i nie może być nieznana!");

            if (father != llama::noname && !isNameInHerd(father->getName()))
                throw std::logic_error(
                    "Ojciec urodzonej lamy musi należeć do stada lub być nieznany.");

            if (mother->getGender() != llama::sex::FEMALE || father->getGender() != llama::sex::MALE)
                throw std::logic_error("Niepoprawna płeć rodzica.");

            members.insert(l);
            std::cout << "W stadzie urodziła się lama " << l->getName() << ".\n";

            (l->getMother())->addChild(l);

            if (father != llama::noname)
                (l->getFather())->addChild(l);
        }

        void purchaseLlama(const std::shared_ptr<llama>& l)
        {
            if (isNameInHerd(l->getName()))
                throw std::logic_error(
                    "Lama o takim imieniu jest już w stadzie!");

            if (l->getFather() != llama::noname || l->getMother() != llama::noname)
                throw std::logic_error(
                    "Rodzice zakupionej lamy powinni być nieznani!");

            members.insert(l);
            std::cout << "Zakupiono lamę " << l->getName() << ".\n";
        }

        void sellLlama(const std::shared_ptr<llama>& l)
        {
            auto llamaToSell = members.find(l);

            if (llamaToSell == members.cend())
                throw std::logic_error("Lama " + l->getName() +
                    " nie może być sprzedana, bo nie należy do stada!");

            if (l->getFather() != llama::noname)
                l->getFather()->removeChild(l);

            if (l->getMother() != llama::noname)
                l->getMother()->removeChild(l);

            members.erase(llamaToSell);
            std::cout << "Sprzedano lamę " << l->getName() << ". Pa pa!\n";
        }
};

/// Ok wytłumaczone weak pointery
/// https://www.geeksforgeeks.org/cpp/weak_ptr-in-cpp/

int main()
{
    herd happyFarm;

    std::shared_ptr<llama> llamaNatalia =
        std::make_shared<llama>("Natalia", llama::sex::FEMALE);
    happyFarm.purchaseLlama(llamaNatalia);

    std::shared_ptr<llama> llamaLudwik =
        std::make_shared<llama>("Ludwik", llama::sex::MALE);
    happyFarm.purchaseLlama(llamaLudwik);

    std::shared_ptr<llama> llamaTomek =
        std::make_shared<llama>(
            "Tomek", llama::sex::MALE, llamaLudwik, llamaNatalia);
    happyFarm.birthLlama(llamaTomek);

    std::shared_ptr<llama> llamaKuba =
        std::make_shared<llama>(
            "Kuba", llama::sex::MALE, llamaLudwik, llamaNatalia);
    happyFarm.birthLlama(llamaKuba);

    std::shared_ptr<llama> llamaKacper =
        std::make_shared<llama>(
            "Kacper", llama::sex::MALE, llamaLudwik, llamaNatalia);
    happyFarm.birthLlama(llamaKacper);
}