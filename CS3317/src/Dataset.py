from itertools import combinations
__dataset = (
    "IPJTUMAOULBGAIJHUGBSOWBWLKKBGKPGTGWCIOBGXAJLGTWCBTGLWTKKKYGWPOJL",
    "BNIPMBSKHSASLLXKPIPLPUVHKHCSJCYAPLUKJGSGPGSLKUBDXGOPKLTLUCWKAUSL",
    "IWTJBGTJGJTWGBJTPKHAXHAGJJXJJKPJTPJHJHJHJHJHJHJHJHJHKUTJJUWXHGHHGALKLPJTPJPGVXPLBJHH",
    "VXTLKZOKMOKAPHXHMLOWZHTPPHKPKIAXPOXKSKSWJSTSGNSHIOTTLPLLMZKUJHXTPWOWHZGAHLWKKPKMPXOTMZJUOPJ",
    "IPZJILPLTHOUKOSTMPJOGLKJFBLPMJKJTLBWWKOMOYJBJPLJSKLFLOSZHGVPGJSLWGXBHOHLVWUKWXXTWJ",
    "PJJAPJJPPJJPJJAPJJPPJJPJJAPJJPPJJPJJAPJJPPJJPJJAPJJPPJJPJJAPJJPJJKJJP",
    "IPOKJOLKHPZUOZJOGGUSPXLOHLTUTOGKJOTOXPGGZPGPVPHOSOJMOJOSIOMGCWWOWUPPPOGULWHVLJGKPLGJPPUKXWSOJIGPSGPWOSMPHBTNKPGPM",
    "IMGHZGSHMLZPZIKSKTXJLWHHOKPOPXPVKXIGAPHGPGWHSLJZJJLSRPKPOWPLWMPPJJFTSGWAGFZAGIGTJKTKXGKASKPPUOW",
    "OKMOKAJHXTMLOKZHTWPHKPRAXPXXKSWNSMUSGJKSKVOTTLALLMTKUHHSTPKOWHZWAHLGKKTFMDJTMGMUJXJPI",
    "RHGHPHAWAOHGLIPGXLGOSGTKWPHPAMOOGPWJHBKOUXLULKWOXPROXGJOLLMWVBGZUXKXHWMUOOXOGXPGGAXPOWPKPZLMIZXOXGXOKI",
    "IPZJJPLLTHUULOSTXTJOGLKJGBLLMMPJPLUWGKOMOYJBZAYUKOFLOSZHGBPHXPLXKJBXKJLAUUOJHWTWWPQ",
    "UGBJOXSFOIJGBUOTTLWGBZAHTGALAVLILSGLAMKVOBKSCGKTHLFJGCMRAGLAHLVLSTAVMFBTPBPLUAVGWT",
    "LVOBTLLXJMOWPWPOHWGOUAARRDPHTPGSHMHXOPKMSPGSMGPXLOHHWPWPZOGTHKOSPSMWKRSZLOGKXOYZPXGIPOLLO",
    "IXMJIWNGMJJOMRGJJPJJJPJJJPJJJPJJJPJJJPJJJPXJOPJJJPJJJPJJPJXJJPJJJPJJJ",
    "KJOBLLXJKJPLUWGWOMOLIJBJALTUKLVLJSBHGBPGWSYKJBSVJSPMZJOWUWWP",
    "UTVCUGHLPIVHVGBLXIHOILWSKPLXTMGKLVAHMBATKTIKSCUHLUAUAOBORMGGZSUBLALSJKKXITLSATGO",
    "JIHKMUBULSGXWPXPCCJIJOTGHPXHOUPKAUAPZHBBPIGXJILJGLPKKHMUWSTGZGMPLKTTLJKWXGZLZIOLGWFTSZJHRUA",
    "MLTWLOHSBAILUZMSGGSTWWLOGCAGLLSHKBWALZUMATHBPZXOPHUABKPSTRPOP",
    "OPJPXJPPMJPPMXPPMJPPXJPPOXPPXJJPJXXPXJPPOJPPMXPPOGPPXXPPOMPPXXPPOXPPXJPQXPPBJPPPXPPX",
    "GWAPXGKWSZTKMKSPBQOGPBLWUKXOXBXOUOXOVPBGOCLMLPBOSGJKKAAYLWKZMKUGXVGPOKKSKOSLKPBAS",
    "LGXZKLGAPWWETBHGLYLLLWPVUODBKMWKHLLGSQAWZXRWXXTRLCJXBXGXKIOSZPSUKKWWFTWXUKSAILKZHLSTWHKPAPMHGTSKXVMSIOSIPOJKWOPWLKXHLL",
    "XHAPXJAJXXXJAJXDJAJXXXJAPXJAHXXXJAJXDJAJXXXJAJXXXJPPXJAJXXXHAPXJAJXXXJAJXXXJAJXXXJA",
    "IGUPWGTKNJJIOKLOLWLTLJLJHTLOLKJLMJTOOLKPWJTBXLLMIAGVOOGAJOLBUAWJJXNPWWUGTMWTUBGJJUJHNSNSGUWGJJUUWKUJJVT",
    "JJXPSPJAHATJAJXHAAJXJXOOGPPPAPHJJHAHJJAKXRJJAPAPAJJPPAPJOPPAJJS",
    "WLGVLKHPVPKLMOHUXILWOIPGLPMHOSKBOGWKLMLGOGPGKLKPWLPHPPGIGKOGGTTBTMGGVLKLLTSAKHGPPKPWRGLKPBGPFVWAPOOPIOKPAIKPGOVX",
    "IJPCPWSTVLSUTOGOGOTGKSAKPXPDRWOIJPQGUAKSBNOMLJGOBRSVJBAGWGLUSLPLKKPP",
    "IGNTIMBBPZJJLKLTHJULOSTXPJOGLKJOPSLMBKJPLUWGKOMOYZWZALPLKLWLTSSHGBPHKTLJKJBXOVLOSOJJKTKVXWXM",
    "PWPCTLLTXALSMKUAKPWXPILXOLWSWTLXBAJACHSPHKOPPXKKWHILFLSPFAKKALJOVXSCPGSSAPLJSGPPKOKWODWXMOKOJGGPXWLKHPOP",
    "IPZJILMLTHMULOSTUAMVOLKJPVLLMOKJPLTWWKOMKYJBOPLGUKOOPLSSTGBPKPPLWKOBMTULJKZKSAPXHUL",
    "FWKPHPJTJJPJAPPJJHKJPKPJJPPJAPPJJJPKJJKKJJPPAJJHPJJPPAJJPPOJKPJJJ",
    "IPUTAMPOJOPOMLXHOOOMUQBOTIKOHVWJJKSHPWZXUSVPPQSPBUPPKAKWSOGPSJLWWZJUJPPOZJTOGUTPKJPGJ",
    "IBKSOKOWBPMPLJLLOLFKTBOOXJBKAJLLASLLSLLOLLUKWGOPSOZKSUGTUGBVXAWWJPJULLZLILJJIPLOPLPSNKJKAGYKKZ",
    "PLKHJKBKKXTLKPEOLKXKLLKMSLOMMRTLGJALXWKPHTLGLJGZSLKJKOKOMTKPLMUPAPQX",
    "ISOMJJKXGUJXSHHWWSLPLTTSHWTLOKUMWOHMWXSHTTSVSOXJGMXOKPJGPLLKPKWJKLPLTXWXIJXJJPOKXSPGZTHOPPKXX",
    "IHOKPHYKOOOOZJJGGJMHOLZJLKOOHGBOOPZXTGWZPGMVTVPZOJJJJLSIOOGCUWOWUPLPOPULBHVTJGKZLGJGLLWXKSOJIGPSGPKOSAJKBPMGKUMPOXZGXPPP",
    "PJJJAPJJJAPJJKPJHPPPJJPHAJJPPPJJLPPJJPHPJJLPPJJPPPJJLPPJJPPJJJT",
    "KJLZOHIJMJUPJBHWLXKKOZJKBABOLKKBSKSAXBPUHXXCCUTWATXWEPJSMABVZGGPXUSSHXVKPVKTXMUGXZDUXXAGOUAMKVMWBXAOSLLMBJAJIWGPZ",
    "IPHJJPLLTTOULOSTPLOOGLKJJVLLMKKBALUWWKOMOYNZALUZKLILJSZTWVTGWXLJKXBJNJTUOHBKTKJAU",
    "ISZGJMJJJCJOOPOJTILKOOOGOWOMKEOGTKZOTTOZWTPMKWSSGJLKHGPPQHGXJSBSLTLTJPSMPKJKYRPXOPJPPLKXPRBSOLCVGVZLOKJPGPXPPOXLLGUB",
    "LLSAHNUAGWAPXGKWSZTKKPSIBYASPBSMUKPGXBZOUOXOBMBGOCLMTPBSSBOKKAAYLWKZMKUWXZGPOKKIHUMMUMPV",
    "IPPJOJPJJJPJOJPPAJOJPKJOJPJJJPPAJOJPJJJPPAJOJPJJJPPAJOJPJJJP",
    "BLGPSGLVCLTLWXSTZFUFQAAFSHAKSHPBBMRFKFWWGGPSBCBHOLBTHLIOGMGOOKXQKXKPPXWPPPGPOVSKSHPXKPWHPLJSGAXMGPXTB",
    "IPJJHMJJPYJJHHGJJHPPJJJSGJPHJJSANHJJPKPJHHJJKJPKKHJJPKPJJHKXJHHJ",
    "TWXKJAHJLMKSSGWSMWLMOKPOLXOPGKHHGHJOITXSGPSVGOXILWJKMVGZTXWSHBXOWSWGOSGOGLKVSKKKLWUGGOXLGSGAXKTGKPW",
    "ULVPKLKKLUMAUMGPLRSWUTTKJPLOBKOHFSPBUWAGWHBFSKALBGAYPMXCLLWWOZLPJGGVPVHXPHKANHWWHOJPVLL",
    "IKBSKKKKWKKKKKKKKWWKKKKPGKKKKKXXGGKRKWWKWKKPKKKKKXKKKRWKMKKPKKWPKKKKKPGKKKLBKWWKKJ",
    "WPIWTJBGTJGJTHGBJOXKHTXHAGJJXJJPPJTPJHJHJHJHJHJHJHJPKUAJJUWXHGHHGALKLPJTPJPGVXPLBJHHJPK",
    "KJHGHLJHWHGSKXQSHWSUKJPNMSJXLWAASMMOGWBPLJMGXSLOHGTSVUWMJXTHGZGROGOLLIMWBKJHGHLJHWHGSKXQ",
    "IPHJJJPJJJPAJOJPJJJPAJOJPPJJJKHJJJPJJJPJJJPAJOJPJJJPHJJJPJJJPAJOJPJJJPHJJ",
    "IQJAKPJAGTPUJAPHPJPQAPJAKPHJPKPHHAPPJAHHPKJAPHPJAPKJAWPJPKPJHPKPPJJ",
    "LKHABOUAPSLSJLTWCLJBSPPJIHKMUBUPSAXKPXLCCHIJOTGKUXGZJPUPUAPZHBBPIGXMMLJGOPWKHMUWSTGZMO",
    "OWPLWIPPJJHZXGWAGFZAGAWHJKNSWXAXOPAATGKKOPHKJKHLMHLKXIXPGHPPPKPFGHWVSIKJPKXOLIOWXLKOGWXJOLLJTLZVOPJS",
    "XPSPJPXPSPPPPXXXPPJPXXPPJPKPXXPXJPJPKXXPXJPPJHPXXXPXXPXIPPIXJXCQIHSSMWXMOHOGWTZXWTSGXOXZTOGMZXBUUJHX",
    "IHBGKLXTFWJFJGLSFKXKFAKSFBVXLAUIGKWSADFWSFPGFXAXFAKSPWBPSDWAXLMXJBGXGUGXGTMWCAKWHZPAPAAGSPSSCOSKJSJGJVGXO",
    "PPJJPJJPPJJPPJJKJJPPJJPPJJGTJJJLJJMTJNLJJTTJUJHOJPGJJPPJJPJUPHJJP",
    "IGSMWPOZLGWSGSKKPMLSGXWSPZZHKXSKLWHGLMPBQPKPSJOLKOOVLZPVKAGDPGTOKKKSGTLELGXCZKABHOPPKSHBSKSGGWXBBOLBKUZPLKHGZWSUGO",
    "IPGHJMXOOLOWJGOWONKJYTSEOITKBOTUJMWTKMGWSSWMLKHGGTKHTMWJSWPXJMYJTXJPPGKLJGKPXJPGPPLWHXKKBSOULVGVZLOKJMGPSPPOXLLGN",
    "ITPVKWKSKXKXUAXPVHXVOMMKHYBPABLLOBGKOLLJGXZGXLSOLAMOGKIGXBATBXMPJTCVMTAXVMPWWAWOMOUPHHZBITKKXLK",
    "IHZKWPMAFWLKJSJPFKSKFAKSFWZLLSPSAMGVWUAUSFWSFHGFKSPFAKMPWBPXXSGAPXCJZBHMKUOSZVPJJ",
    "LTHJULOSTKTJOGLCJJGPZTOKJHLPWGKOMOLMJBXALMUKLMLJSBHGBPGJSLWKOIXTLBJLJJPKTRSBXXLSSK",
    "COCLCOCGPOBTTZGPOCGHLWXWZALPHWLOOKBWSZLILWKWLXHPXWLSSFHGVZLKHGLYJCUZLJOZAHGLOLKKW",
    "LPLTTOULOSTMTJOGLKJGBLLMKPJPLUWWKOMOYOZUPYUKLGLJSZHGBPGHSLXKXBOJOJSUJKBKTKJAKTX",
    "MIPRJPLTJSUPLZSLJHLOROMTGPHPKAOGXPXJLGOHMOOLXOMJLOJOXSSAXOWFUT",
    "IPOTWJJLABKSGZGWJJKSPPOPHTSJEWJHCTOOTHRAXBKLBHWPKZULJPZKAKVKHXUIKLZJGLXBTGHOHBJLZPPSJJPJO",
    "IPZJJLGLTTOULOSTKTJOGLKJKBPLMJKHLLXWWKOMOYJBJALOLPLWLOSSHWBPWPPLOKXBJHLOJLOGWTWGAS",
    "IPZJJPLLTTOULOSTPLOOGLWJJBLLXWKWTLUWWKOMOYJBZAYUKLWLJSZHGBPKJULJKUBHJJOJOHGKTKWAT",
    "LPPPPOTAKHNPRAPMKPSMWPPLXKKXEQKKJXGKXUPGSPLPOHWOKLWXULLJHGWOKTSSLXLITOXSPXGPGPOZPHTNOLPPSGW",
    "IJGUMWTSUXLPOJJOIOKLGLKLTLJLJHTLOLKJLMJTOOLKPWULBXLLMIAWVIOGAJOLBHABTPJTVPXKUWLNXSPKJPLJGUPJJHWSPSPGWPPLKKOOTJS",
    "ITXXGKWAPPUVLPSTWMRXLGXPKOJEPIVWLSKLKJLGZZGKVXKKSUTWDPGPLZFJUWSKHWZXSUTWTKJSSLOLWAHPIZHJXJO",
    "HIPHSHPJRSHGLJIHRXGKXGJJPWXXXCLKHPPPAKPKPPPLPAPPLLSLPPPPXXJSTBSKRHPPLSJNMKWJKKOPPHLG",
    "IPMJJLLLTHOULOSTMAJIGLKJPVLLXGKTPLTWWKOMOYJBZPYUKLILOSZHGBPGWXLZKJBSWJLPJUUMHKTRAP",
    "TGAXPCSBPOXFLBAGWWEPVHGLYLLLIPOZXDBXSKKOOLGMQAWMMRKXOTGHLCJXWXVXKIOSLPSUFWHKFUIXUGSAILKZHLSTWKKPATMHGHSJXVMIGOTQGNWOLGLW",
    "WTXHHJJTJHTNTJHTJHHJJTJHHJHHJHOJHPJHHJHHNTJHHJHHJHTJHHJHWJPH",
    "ITOJLLLULSTKSPPMOGKJLWXOGOOKWLLSKPKWSOBVOQGRBSPPPBXUALLPKPOM",
    "JJHHJOJPAPJHHPJJQPJJAPPJJPJHHAPJLJLJPJLJJTIULJJKFGHLNTIJOTSPKPPWXPPL",
    "KLPLLPILPISQTIIJAPGPOLXGOFKLPHHADVOOVWXJSTPGXOOBPAWCKXXATKXSHWXIGVLGOSOVXPZZUKTBH",
    "GIKPKSTWAPWBLWHOSTBWKBHTUKBPWGLGOPGVBGGPLIWSROGLVPSFZOSHXGKVAPHLPAAPJPLFOLLEAPAZOLAKOLGGCKLAGWOLK",
    "ZWSPZZHKXSWLWHGLMPGPMPPLSJJLKOOVLZPVKAGDPGTOKKWSGTLELGXVZKSBAOPOWLXBSKSGGZXBBMLBPUZPGKHGZKZFGMLJ",
    "IPZHJPMJPKJLUOSTKLOOGLKNVLLXNOWLTWWGOMOLGOKZALKYXQJSZHWBPGNLJKXBKJJMLJMVKHKJ",
    "TOIOKAOFTLWGGZAHTGALOVLWLSGLZXPVOBKSBGKPPMMTGCMWGAGLAHLVLSTAVMFGTPBPLUAGGITASGGKHSLGGHAPXKOSKATBAPXM",
    "IMPJLTKZLSTATOGXALBPHSZTBGJALSSWGMKBLLTPZVBGKKPPWLWBPBXSSOXFAKKH",
    "HPJOJKPJJPHHPOJPKJJPKJJPHPJJPPAJJPPAJJPPJJPKOJPPAOJHKJJPPJJPPOJ",
    "SVSTFKPPKPNMDKLAWSWGWUUPLWHOSHHBJJIHJKSCZPKKTHUGSTKBUIFJAKKSLIKXOLCLOKWUKTTKULMJLPBLMHUVTPPJPLIZLBHJPGPGXKPJJLKH",
    "IXWJIXOSPJBNLXWKJZJBGTBOLKWBSKSAHBUUHDCCGTWAXXIEJJSMABVZGGPXUSKHXVKPVKTXMUGGSSWUJSAKOZAMKDGBTSBJULTVMWTXPJIZ",
    "JKWOKSPEXBBJZGPLKHSAXPJONWLOXBKXKBMOXPHJGAPPJCGPMYWVASKWXTPLPJTJJPZUWJTZZUKLLGASHGUGJGGXAGOXGBJDKOTGLGXGLGAOXIWBOZABALA",
    "LKSAPGILILIKAPHOJPGXOPLGTGSMWXKBXKUXPBQKPKPHPOXGLWAXXJGUAGLLPWPGLZAWLQLPRPKJGGZXGPOOMPOBLGPHGFWLLLILWPPWBXOG",
    "IBLTWLIAXGWWWGKWPGWWBLAOJGAXGLOTGLJTWLXBJOQUXGOTHGXXXWOWXXMOXOPHAPPPPHAPPPHAPPPHAPPPHAATAHAAAHKXMAHAKTOHZYLP",
    "HZJGGTASKJBJOGLGGWWDXZOBLKOZJXPIJPIOPXKSRHGHPHAWAOHGLIPGXLGOXGTKWPHPAMOOGPWJHBKOTXUJTKWOXPROXGUOLLMKVBGZUXKXHWPUOOIMGXX",
    "IHKOMGTXTWKUOWPPLXKKXEQKKJXGKXUPGSPLPHOKXKIHSLLLOOGKOKPSSLPLITOSSGPGPKXOZPHTJGTLSSGGSWOHGLBOLXP",
    "CKTWLPGJTJJGLGJLSPPAXAJPJPJPJPJPJPJPJPJPJKJPJXSTLXHJJOSAKPBHVBAGCPJ",
    "GVWLPRKXTKXOBLGHXGLVCYLKXSTOFUFQAAFLGACGLPLWMPKPKTVWBGLSBCBHOLBPJLIOGMGGOKXTTKMKQNPPPGPOVSKSPPSTPWTXYSGAXXGL",
    "LPWXMTBLTBSJBJXXBTUPPJJZBLTLCPCGKPLTSLJGBKTSHGUMSUAGISKKSJJYAGGFGSKCXZPVVGMVMUOOKXVKSJBCSWKUC",
    "XMUHTBUSZVGXKSVSGTSKIBKHHPUHGUWGAAGGSOIXKWOGPLVHXDNUWPUJBGGAJMWJSULKJXJXIUGTSSWWJXWWOUUHJXTLKOUGXOXWTJKPOJ",
    "PPXSLAMLXALVKVJAVAUTVCUGTLPHVPVKBPOGPPWLWSWPLXTMGKLVAHMBATKTIKSCXHLPAUPOCORXGGJUUBLALS",
    "IJGKPHGWPLGBPKHPBPPXAPJJXXJJPSPJAPQPAPPJAPSJJPXAPJTSPJPLSJJPXPPJJ",
    "XLPISQUIGJAPGPOLXGOFKLPHHGDBOJZWXJSPPGXOOBMAKBKLXAHKXSHKPWGOLGJXOVXKZZLWOWTSTPWKPPPHGTUOVWHSO",
    "GXXXKOTJIAOTGJJLABKSGTGTJJKSGPUPUUSJJAWJHCTOOTIWWATIKLGHWTKZULOMZKAWBWUXSIKLZJGLXBPWHOHBJIZTLSOJP",
    "IPHPJJHHJJPJJKPJJPHJJJKHJJJPPAJJJPPJJJKHJJJPPJJJKPJJJKPJJJKPJJJK",
    "ITNHXHWJGTJJPJXGPGJIJXJPJJGHJJUKSTJLUHWTAGOLMTPUMPJHMJAKXUMOOV",
    "IPSWJNJXXGSJGHRXPPXGKHIGXXXCLKTPPPAKPKPPKPPLLSPLXSLSPJHXBSKKWJSHLAJNXKWJPWOPWHTGLGJSPJSIPXPPSTNGXPKLJXPPXSPJJMGXXPLPHWRP",
)

def dataset_single_size():
    return len(__dataset)

def dataset_combination_size():
    return int(len(__dataset)*(len(__dataset)-1)/2)

def dataset_combination():
    return combinations(__dataset,2)

def dataset_single():
    return iter(map(lambda x:(x,),__dataset))