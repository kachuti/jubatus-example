#include "normalize_num_filter.hpp"

const std::string& get_or_die(const std::map<std::string, std::string> & params,
                         const std::string& key) {
  std::map<std::string, std::string>::const_iterator it = params.find(key);
  if (it == params.end()) {
    throw JUBATUS_EXCEPTION(jubatus::core::fv_converter::converter_exception(std::string("\"" + key +  "\" is not specified in parameters")));
  }
  return it->second;
}


normalize_num_filter::normalize_num_filter(double max, double min)
 :min_val(min),max_val(max){};


double normalize_num_filter::filter(double value) const{
  return (value - min_val) / (max_val - min_val);
}


extern "C" {
  jubatus::core::fv_converter::num_filter* create(std::map<std::string, std::string>& params) {
    const std::string& min_str = get_or_die(params, "min");
    const std::string& max_str = get_or_die(params, "max");
    double min_ = jubatus::util::lang::lexical_cast<double>(min_str);
    double max_ = jubatus::util::lang::lexical_cast<double>(max_str);
    if (min_ == max_) {
      throw JUBATUS_EXCEPTION(jubatus::core::fv_converter::converter_exception(std::string("MAX equals to MIN.")));
    }
    return new normalize_num_filter(max_, min_);
  }
}

