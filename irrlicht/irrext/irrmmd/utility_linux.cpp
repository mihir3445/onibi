#ifndef _WIN32
#include <iconv.h>

namespace util {

	std::string dirname(const std::string &path)
	{
		std::string::size_type found=path.find_last_of('/');
		if(found==std::string::npos){
			return "";
		}

		return path.substr(0, found);
	}

	std::string convert(const std::string &text,
			const char *fromcode, const char *tocode)
	{
		iconv_t cd=iconv_open(tocode, fromcode);
		if(cd==(iconv_t)-1){
			return "";
		}
		// iconv��API�ɂ��킹��
		char *inbuf=const_cast<char*>(text.c_str());
		size_t inbytesleft=text.size();
		// outbuf
		std::vector<char> buf(inbytesleft*2);
		// �ϊ��ςݕ����̍Ō��
		char *outbuf=&buf[0];
		size_t outbytesleft=buf.size();
		while(inbytesleft){
			int ret=iconv(cd, &inbuf, &inbytesleft, &outbuf, &outbytesleft);
			if(ret==-1){
				return "";
			}
		}
		iconv_close(cd);
		return std::string(buf.begin(), buf.begin()+(buf.size()-outbytesleft));
	}

	std::string cp932_to_fs(const std::string &text)
	{
		return convert(text, "CP932", "UTF-8");
	}

}

#endif
