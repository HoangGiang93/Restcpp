#include <curlpp/cURLpp.hpp>
#include <curlpp/Options.hpp>
#include <sstream>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/reader.h>

int main(int, char **)
{
  // That's all that is needed to do cleanup of used resources (RAII style).
  curlpp::Cleanup myCleanup;

  // Read data as a string
  std::stringstream os;
  os << curlpp::options::Url(std::string("http://ked.informatik.uni-bremen.de:8090/k4r-core/api/v0/stores/4"));
  std::string data = os.str();

  // Convert the string to json
  Json::Value data_json;
  Json::Reader reader;
  reader.parse(data, data_json);
  // Print the data
  std::cout << data_json << std::endl;
  std::cout << "-------------" << std::endl;

  // Filter data
  std::string addressCity = data_json["addressCity"].asString();
  // Print the filtered data
  std::cout << addressCity << std::endl;

  return 0;
}