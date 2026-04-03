# STANAG 4586 DLI SDK - Technical Backlog & Roadmap (v2.x)

Bu döküman, Twin-Architecture refaktörü sonrasında SDK'nın ürünleşme, doğrulama ve bakım kalitesini yükseltmek için öncelikli teknik işleri listeler. Amaç yeni özellik eklemekten önce mevcut mimariyi daha öngörülebilir, daha denetlenebilir ve daha kolay tüketilebilir hale getirmektir.

## 1. Critical Near-Term

### 1. Generator Input Validation
- **Problem**: Jeneratörler bozuk veya eksik `.sdli` girişlerinde çoğu zaman geç fail ediyor ya da düşük sinyalli hatalar üretiyor.
- **Goal**: Generator katmanında erken, açık ve deterministik doğrulama sağlamak.
- **Actions**:
- `.sdli` dosyaları için şema ve mantıksal kural doğrulaması ekle.
- Geçersiz tip, tekrar eden alan adı, çakışan `pv_bit`, eksik `pv` tanımı ve desteklenmeyen ölçekleme kurallarını açık hata olarak yakala.
- C++ ve Python jeneratörlerinin aynı doğrulama mantığını paylaşmasını sağla.
- **Expected Outcome**: Kötü girişler artefact üretmeden önce açıklayıcı hata mesajlarıyla durdurulur.

### 2. Test Layering
- **Problem**: Saf mantık testleri ile ortam bağımlı ağ testleri aynı test yüzeyinde duruyor.
- **Goal**: Testleri çalışma ortamı bağımlılığına göre ayrıştırmak.
- **Actions**:
- Testleri `unit`, `integration` ve `smoke` olarak sınıflandır.
- `TransportTest` benzeri gerçek soket kullanan testleri açık şekilde `host-only integration test` olarak işaretle.
- CI içinde varsayılan olarak unit testleri koş; integration testleri koşullu veya ayrı job olarak çalıştır.
- **Expected Outcome**: Sandbox/CI kaynaklı false negative sayısı düşer; kırılan katman daha net anlaşılır.

### 3. Unified Regen & Verify Workflow
- **Problem**: Kod üretimi, build ve test akışı manuel ve operatör bilgisine bağlı.
- **Goal**: Tek komutla tekrar üretilebilir doğrulama akışı sağlamak.
- **Actions**:
- `generate -> build -> ctest -> python verify` zincirini çalıştıran tek bir workflow ekle.
- Bu akışı `tools/full_verify.py`, `Makefile` veya eşdeğer bir görev komutuyla standartlaştır.
- Host-only testler ile sandbox-safe testleri ayrı seçeneklerle sun.
- **Expected Outcome**: Geliştirici ve CI aynı doğrulama akışını kullanır.

## 2. Operational Quality

### 4. Generated Artifact Policy
- **Problem**: Üretilen dosyaların repoda tutulma politikası tam net değil.
- **Goal**: SSOT ile generated artefact ilişkisini operasyonel olarak sabitlemek.
- **Actions**:
- Aşağıdaki modellerden birini açıkça seç ve dokümante et:
- `generated code committed`
- `generated code ephemeral`
- `.gitignore`, CI ve release akışını seçilen modele göre hizala.
- Generator çalıştırılmadan commit alınamayacaksa bunu tooling ile zorunlu hale getir.
- **Expected Outcome**: Repoda stale artefact, gereksiz diff ve belirsiz sahiplik azalır.

### 5. Packaging & Consumption Story
- **Problem**: SDK'nın dış projeler tarafından nasıl tüketileceği henüz ürün seviyesinde tanımlı değil.
- **Goal**: C++ ve Python tarafı için net tüketim modeli sağlamak.
- **Actions**:
- C++ için `find_package(dli)` akışını destekleyen `Config.cmake` ve install/export tanımları ekle.
- Python için `pyproject.toml` tabanlı paketleme akışı oluştur.
- Harici kullanıcı için kısa entegrasyon örnekleri ekle.
- **Expected Outcome**: SDK yalnızca repo içi değil, dış projelerde de öngörülebilir şekilde kullanılabilir.

### 6. Meaningful Error Reporting
- **Problem**: Parser, generator ve serialization katmanlarında hatalar yeterince açıklayıcı değil.
- **Goal**: Operasyonel hata ayıklama süresini düşürmek.
- **Actions**:
- Generator doğrulama hatalarında dosya adı, alan adı ve mümkünse satır bağlamı döndür.
- `BitCursor` ve parser katmanında hatayı yalnızca fail etmek yerine nedenini taşıyan bir model geliştir.
- `validate` benzeri ayrı bir doğrulama komutu eklemeyi değerlendir.
- **Expected Outcome**: Hata alan geliştirici doğrudan problemi görebilir; yeniden üretim maliyeti azalır.

## 3. Medium-Term Expansion

### 7. Python Profile Filtering
- **Problem**: C++ tarafındaki LOI/Profile mantığının tam simetrisi Python tarafında henüz yok.
- **Goal**: Twin-Architecture iddiasını profile enforcement tarafında tamamlamak.
- **Actions**:
- Python için `profiles` modülü ekle.
- C++ tarafındaki generated profile mantığını Python tarafına taşı.
- Profile filter davranışını Python testleriyle doğrula.
- **Expected Outcome**: Python SDK yalnızca parser değil, policy-aware runtime yüzeyi de sunar.

### 8. Multicast Compliance & Adapter Boundaries
- **Problem**: Transport katmanının genişletilmesi, standart gereği zorunlu multicast davranışıyla çelişebilecek yanlış bir mimari yön oluşturabilir.
- **Goal**: Multicast'i birincil ve zorunlu taşıma modeli olarak netleştirmek; olası diğer giriş/çıkış mekanizmalarını bunun etrafında doğru konumlandırmak.
- **Actions**:
- `MulticastTransport` için standart uyumluluk beklentilerini açıkça dokümante et.
- Ağ bağımlı testler, host-only doğrulama ve operasyonel sınırlamalar için net test politikası oluştur.
- Serial veya diğer I/O yüzeyleri eklenecekse bunları bağımsız primary transport olarak değil, multicast omurgasına bağlanan adapter/bridge sınırında tanımla.
- **Expected Outcome**: Transport mimarisi standartla uyumlu kalır; ileride eklenecek adaptörler çekirdek iletişim modelini bozmaz.

### 9. Versioned API Documentation
- **Problem**: Stabil ve deneysel yüzeyler net ayrılmadığında dış kullanıcı için sürüm riski büyür.
- **Goal**: Semantik sürümleme ve API beklentilerini disipline etmek.
- **Actions**:
- Public API yüzeyini tanımla.
- Stabil, deneysel ve internal alanları ayır.
- Versiyon geçişlerinde kırıcı değişiklik politikasını dokümante et.
- **Expected Outcome**: SDK sürüm geçişleri daha güvenilir ve tahmin edilebilir hale gelir.

## 4. Suggested Execution Order

1. Generator Input Validation
2. Test Layering
3. Unified Regen & Verify Workflow
4. Generated Artifact Policy
5. Meaningful Error Reporting
6. Packaging & Consumption Story
7. Python Profile Filtering
8. Multicast Compliance & Adapter Boundaries
9. Versioned API Documentation

---
Bu backlog yaşayan bir dökümandır. Yeni iş eklenirken öncelik, doğrulanabilir çıktı ve operasyonel etki birlikte değerlendirilmelidir.
