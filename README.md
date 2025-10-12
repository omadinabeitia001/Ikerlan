# 🔐 Ikerlan — Cryptopals Crypto Challenges (Set 1, 2, 3)

Biltegi honetan [Cryptopals Crypto Challenges](https://cryptopals.com/) webguneko **1., 2. eta 3. set-ak** inplementatu ditut. Ariketa hauek kriptografiaren oinarriak lantzen dituzte, eta benetako eraso teknikak ulertzeko eta praktikan jartzeko aukera ematen dute.

## Helburua
Proiektu honen helburua kriptografiaren oinarriak sakonki ulertzea da, eta horretarako ariketa praktikoak egitea, eraso errealak simulatuz eta defentsa teknikak aztertuz. C++ erabiliz, errendimendua eta kontrola mantentzen dira, eta CMake + GoogleTest bidezko egitura modularra erabilita, testak eta mantentze-lanak errazten dira.

## ✅ Egindako ariketak

### 🔹 Set 1: Basics  
- Hex ↔ Base64 bihurketak  
- XOR eragiketak  
- ECB zifratuen detekzioa  

### 🔹 Set 2: Block Crypto  
- AES CBC moduan inplementatzea  
- PKCS#7 padding eta padding orakuluak  
- ECB vs CBC detekzioa  

### 🔹 Set 3: Block & Stream Crypto  
- CTR modua eta bere erabilera  
- Estatistika bidezko erasoak  
- MT19937 PRNG: egoeraren klonazioa eta berreskuratzea  
- Stream cipher bat MT19937 erabiliz eta bere aurkako erasoak  
- Token faltsutzea denboran oinarritutako seed erabiliz  

## 🗂️ Proiektuaren egitura
<pre>
Set3/
├── include/         # Header fitxategiak (.hpp): interfazeak eta definizioak
├── src/             # Inplementazio nagusiak (.cpp): algoritmoak eta logika
├── tests/           # Unit test-ak GoogleTest erabiliz
├── data/            # Sarrerako fitxategiak (.txt)
├── CMakeLists.txt   # Eraikuntza konfigurazioa CMake bidez
</pre>

## 🛠️ Erabilitako teknologia

- **Lengoaia:** C++
- **Build sistema:** CMake  
- **Testing framework:** GoogleTest  
- **Kriptografia liburutegia:** OpenSSL  

## 🚀 Exekutatzeko

```bash
mkdir build
cd build
cmake ..
make -j
ctest --output-on-failure
