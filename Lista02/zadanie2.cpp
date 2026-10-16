#include <iostream>
#include <fstream>
#include <memory>
#include <string>

class line_writer
{
    private:
        std::ofstream file;

    public:
        line_writer(const std::string& filename) {
            file.open(filename, std::ios::app);

            if (!file.is_open())
                throw std::runtime_error("Nie można otworzyc pliku: " + filename);
        }

        ~line_writer() {
            file.close();
        }

        void append(const std::string& text) {
            file << text << "\n";
        }
};

int main(int argc, char** argv)
{
    std::string filename =
        (argc == 2) ?  argv[1] : "example.txt";

    std::shared_ptr<line_writer> ptr1 =
        std::make_shared<line_writer>(filename);
    ptr1->append("ptr1 wita.");

    std::shared_ptr<line_writer> ptr2 = ptr1;
    ptr2->append("ptr2 pisze.");

    std::shared_ptr<line_writer> ptr3 = ptr1;
    ptr3->append("ptr3 pisze.");

    return 0;
}
