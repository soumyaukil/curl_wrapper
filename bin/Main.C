#include <HttpClient.H>
#include <iostream>
#include <sstream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <sha256.h>


std::string getAuthorizationToken(const std::string &username, const std::string &password);
std::string prepareHashForAFile(const std::string &filename);
std::string registerFile(const std::string &token, const std::string &hash);

int main()
{
  std::string idToken = getAuthorizationToken("", "");
  std::string hash = prepareHashForAFile("./Makefile");
  std::string entityId = registerFile(idToken, hash);

  std::cout << "IdToken: " << idToken << std::endl;
  std::cout << "Hash: " << hash << std::endl;
  std::cout << "EntityId: " << entityId << std::endl;
  return 0;
}


/**
 * Find authorization token using a given username and password
 */
std::string getAuthorizationToken(const std::string &username, const std::string &password)
{
  HttpClient httpClient;
  const char *url = "https://demo.pencildata.com:8443/users/tokens";

  std::string postFieldJsonString;
  std::map<std::string, std::string> headers, postFields;
  nlohmann::json postFieldJson;

  headers["Content-Type"] = "application/json";
  postFieldJson["username"]  = username;
  postFieldJson["password"]  = password;


  postFieldJsonString = postFieldJson.dump();
  nlohmann::json tokenResponse = nlohmann::json::parse(httpClient.doPOST(url, headers, postFieldJsonString));
  std::cout << tokenResponse << std::endl;
  return tokenResponse["result"]["idToken"].get<std::string>();
}

std::string prepareHashForAFile(const std::string &filename)
{
  SHA256 sha256;
  const size_t bufferSize = 144*7*1024;
  char* buffer = new char[bufferSize];

  std::ifstream file;
  std::istream* input = NULL;
  
  // open file
  file.open(filename.c_str(), std::ios::in | std::ios::binary);
  if (!file)
  {
    std::cerr << "Can't open '" << filename << "'" << std::endl;
    exit(1);
  }
  while(file)
  {
     file.read(buffer, bufferSize);
     std::size_t numBytesRead = size_t(file.gcount());

     sha256.add(buffer, numBytesRead);
  }
  // clean up
  file.close();
  delete[] buffer;
  return sha256.getHash();
}

std::string registerFile(const std::string &token, const std::string &hash)
{
  HttpClient httpClient;
  const char *url = "https://demo.pencildata.com:8888/controller_service/v0.2/register/";
  std::string postFieldJsonString;
  std::map<std::string, std::string> headers, postFields;
  nlohmann::json postFieldJson;

  headers["Authorizatio"] = "Bearer " + token;
  postFieldJson["hash"]  = hash;

  postFieldJsonString = postFieldJson.dump();
  std::string entityId = httpClient.doPOST(url, headers, postFieldJsonString);
  return entityId;
}
