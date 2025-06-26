// EncryptionCoding.cpp : 
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cassert>


std::string read_file(const std::string& filename)
{
    std::ifstream infile(filename, std::ios::in | std::ios::binary);
    assert(infile && "Failed to open input file in read_file()");

    std::ostringstream buffer;
    buffer << infile.rdbuf();
    return buffer.str();
}


std::string get_student_name(const std::string& full_text)
{
    // Find the first newline character
    size_t newline_pos = full_text.find('\n');
    if (newline_pos == std::string::npos) {
        // If no newline is found, treat the entire text as the name.
        return full_text;
    }
    // Return everything from index 0 up to (but not including) the newline
    return full_text.substr(0, newline_pos);
}


std::string encrypt_decrypt(const std::string& source, const std::string& key)
{
    size_t key_length = key.length();
    size_t source_length = source.length();

    assert(key_length > 0);
    assert(source_length > 0);

    std::string output;
    output.resize(source_length);

    for (size_t i = 0; i < source_length; ++i) {
        // XOR each byte of source with the byte of key at position (i % key_length)
        output[i] = static_cast<char>(source[i] ^ key[i % key_length]);
    }

    assert(output.length() == source_length);
    return output;
}


void save_data_file(const std::string& filename,
    const std::string& student_name,
    const std::string& key,
    const std::string& data)
{
    std::ofstream out(filename, std::ios::out | std::ios::binary);
    assert(out && "Failed to open output file in save_data_file()");

    // 1) Student name
    out << student_name << "\n";

    // 2) Timestamp (formatted as YYYY-MM-DD) using localtime_s (global namespace)
    std::time_t t = std::time(nullptr);

    std::tm local_tm_struct;
    errno_t err = ::localtime_s(&local_tm_struct, &t);
    assert(err == 0 && "localtime_s failed");

    char date_buf[11]; // "YYYY-MM-DD" + '\0'
    std::strftime(date_buf, sizeof(date_buf), "%Y-%m-%d", &local_tm_struct);
    out << date_buf << "\n";

    // 3) Key used
    out << key << "\n";

    // 4) Raw (possibly binary) data
    out << data;

    out.close();
}

int main()
{
    // These filenames must match exactly what the assignment calls for:
    const std::string file_name = "inputdatafile.txt";
    const std::string encrypted_file_name = "encrypteddatafile.txt";
    const std::string decrypted_file_name = "decrytpteddatafile.txt";

    // 1) Load the entire input file into one big string
    const std::string source_string = read_file(file_name);

    // 2) Extract student name from the first line
    const std::string student_name = get_student_name(source_string);

    // 3) Define your XOR key (as per assignment instructions, you can choose this)
    const std::string key = "password";

    // 4) Encrypt the source_string using XOR
    const std::string encrypted_string = encrypt_decrypt(source_string, key);

    // 5) Save the encrypted result with a three-line header + raw data
    save_data_file(encrypted_file_name, student_name, key, encrypted_string);

    // 6) Decrypt back to plaintext
    const std::string decrypted_string = encrypt_decrypt(encrypted_string, key);

    // 7) Save the decrypted result (it should match the original file_text)
    save_data_file(decrypted_file_name, student_name, key, decrypted_string);

    // 8) Print a summary to the console (using plain ASCII arrows)
    std::cout << "Read File:  " << file_name
        << "  ->  Encrypted To:  " << encrypted_file_name
        << "  ->  Decrypted To:  " << decrypted_file_name
        << "\n";

    return 0;
}
