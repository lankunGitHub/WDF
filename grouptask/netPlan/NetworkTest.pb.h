// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: NetworkTest.proto
// Protobuf C++ Version: 4.25.3

#ifndef GOOGLE_PROTOBUF_INCLUDED_NetworkTest_2eproto_2epb_2eh
#define GOOGLE_PROTOBUF_INCLUDED_NetworkTest_2eproto_2epb_2eh

#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/port_def.inc"
#if PROTOBUF_VERSION < 4025000
#error "This file was generated by a newer version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please update"
#error "your headers."
#endif  // PROTOBUF_VERSION

#if 4025003 < PROTOBUF_MIN_PROTOC_VERSION
#error "This file was generated by an older version of protoc which is"
#error "incompatible with your Protocol Buffer headers. Please"
#error "regenerate this file with a newer version of protoc."
#endif  // PROTOBUF_MIN_PROTOC_VERSION
#include "google/protobuf/port_undef.inc"
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_NetworkTest_2eproto

namespace google {
namespace protobuf {
namespace internal {
class AnyMetadata;
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_NetworkTest_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_NetworkTest_2eproto;
namespace NetworkTest {
class Query;
struct QueryDefaultTypeInternal;
extern QueryDefaultTypeInternal _Query_default_instance_;
class Register;
struct RegisterDefaultTypeInternal;
extern RegisterDefaultTypeInternal _Register_default_instance_;
class Result;
struct ResultDefaultTypeInternal;
extern ResultDefaultTypeInternal _Result_default_instance_;
}  // namespace NetworkTest
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace NetworkTest {

// ===================================================================


// -------------------------------------------------------------------

class Result final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:NetworkTest.Result) */ {
 public:
  inline Result() : Result(nullptr) {}
  ~Result() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR Result(::google::protobuf::internal::ConstantInitialized);

  inline Result(const Result& from)
      : Result(nullptr, from) {}
  Result(Result&& from) noexcept
    : Result() {
    *this = ::std::move(from);
  }

  inline Result& operator=(const Result& from) {
    CopyFrom(from);
    return *this;
  }
  inline Result& operator=(Result&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Result& default_instance() {
    return *internal_default_instance();
  }
  static inline const Result* internal_default_instance() {
    return reinterpret_cast<const Result*>(
               &_Result_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    2;

  friend void swap(Result& a, Result& b) {
    a.Swap(&b);
  }
  inline void Swap(Result* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr &&
        GetArena() == other->GetArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Result* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Result* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Result>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const Result& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const Result& from) {
    Result::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  ::google::protobuf::internal::CachedSize* AccessCachedSize() const final;
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(Result* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "NetworkTest.Result";
  }
  protected:
  explicit Result(::google::protobuf::Arena* arena);
  Result(::google::protobuf::Arena* arena, const Result& from);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
    kReasonFieldNumber = 2,
  };
  // uint32 id = 1;
  void clear_id() ;
  ::uint32_t id() const;
  void set_id(::uint32_t value);

  private:
  ::uint32_t _internal_id() const;
  void _internal_set_id(::uint32_t value);

  public:
  // uint32 reason = 2;
  void clear_reason() ;
  ::uint32_t reason() const;
  void set_reason(::uint32_t value);

  private:
  ::uint32_t _internal_reason() const;
  void _internal_set_reason(::uint32_t value);

  public:
  // @@protoc_insertion_point(class_scope:NetworkTest.Result)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      1, 2, 0,
      0, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {

        inline explicit constexpr Impl_(
            ::google::protobuf::internal::ConstantInitialized) noexcept;
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena);
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena, const Impl_& from);
    ::uint32_t id_;
    ::uint32_t reason_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_NetworkTest_2eproto;
};// -------------------------------------------------------------------

class Register final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:NetworkTest.Register) */ {
 public:
  inline Register() : Register(nullptr) {}
  ~Register() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR Register(::google::protobuf::internal::ConstantInitialized);

  inline Register(const Register& from)
      : Register(nullptr, from) {}
  Register(Register&& from) noexcept
    : Register() {
    *this = ::std::move(from);
  }

  inline Register& operator=(const Register& from) {
    CopyFrom(from);
    return *this;
  }
  inline Register& operator=(Register&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Register& default_instance() {
    return *internal_default_instance();
  }
  static inline const Register* internal_default_instance() {
    return reinterpret_cast<const Register*>(
               &_Register_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(Register& a, Register& b) {
    a.Swap(&b);
  }
  inline void Swap(Register* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr &&
        GetArena() == other->GetArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Register* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Register* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Register>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const Register& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const Register& from) {
    Register::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  ::google::protobuf::internal::CachedSize* AccessCachedSize() const final;
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(Register* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "NetworkTest.Register";
  }
  protected:
  explicit Register(::google::protobuf::Arena* arena);
  Register(::google::protobuf::Arena* arena, const Register& from);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kContentFieldNumber = 2,
  };
  // bytes content = 2;
  void clear_content() ;
  const std::string& content() const;
  template <typename Arg_ = const std::string&, typename... Args_>
  void set_content(Arg_&& arg, Args_... args);
  std::string* mutable_content();
  PROTOBUF_NODISCARD std::string* release_content();
  void set_allocated_content(std::string* value);

  private:
  const std::string& _internal_content() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_content(
      const std::string& value);
  std::string* _internal_mutable_content();

  public:
  // @@protoc_insertion_point(class_scope:NetworkTest.Register)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      0, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {

        inline explicit constexpr Impl_(
            ::google::protobuf::internal::ConstantInitialized) noexcept;
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena);
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena, const Impl_& from);
    ::google::protobuf::internal::ArenaStringPtr content_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_NetworkTest_2eproto;
};// -------------------------------------------------------------------

class Query final :
    public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:NetworkTest.Query) */ {
 public:
  inline Query() : Query(nullptr) {}
  ~Query() override;
  template<typename = void>
  explicit PROTOBUF_CONSTEXPR Query(::google::protobuf::internal::ConstantInitialized);

  inline Query(const Query& from)
      : Query(nullptr, from) {}
  Query(Query&& from) noexcept
    : Query() {
    *this = ::std::move(from);
  }

  inline Query& operator=(const Query& from) {
    CopyFrom(from);
    return *this;
  }
  inline Query& operator=(Query&& from) noexcept {
    if (this == &from) return *this;
    if (GetArena() == from.GetArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const Query& default_instance() {
    return *internal_default_instance();
  }
  static inline const Query* internal_default_instance() {
    return reinterpret_cast<const Query*>(
               &_Query_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(Query& a, Query& b) {
    a.Swap(&b);
  }
  inline void Swap(Query* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() != nullptr &&
        GetArena() == other->GetArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetArena() == other->GetArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(Query* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  Query* New(::google::protobuf::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<Query>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const Query& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom( const Query& from) {
    Query::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::google::protobuf::Message& to_msg, const ::google::protobuf::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  ::size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::google::protobuf::internal::ParseContext* ctx) final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target, ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  ::google::protobuf::internal::CachedSize* AccessCachedSize() const final;
  void SharedCtor(::google::protobuf::Arena* arena);
  void SharedDtor();
  void InternalSwap(Query* other);

  private:
  friend class ::google::protobuf::internal::AnyMetadata;
  static ::absl::string_view FullMessageName() {
    return "NetworkTest.Query";
  }
  protected:
  explicit Query(::google::protobuf::Arena* arena);
  Query(::google::protobuf::Arena* arena, const Query& from);
  public:

  static const ClassData _class_data_;
  const ::google::protobuf::Message::ClassData*GetClassData() const final;

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kIdFieldNumber = 1,
  };
  // uint32 id = 1;
  void clear_id() ;
  ::uint32_t id() const;
  void set_id(::uint32_t value);

  private:
  ::uint32_t _internal_id() const;
  void _internal_set_id(::uint32_t value);

  public:
  // @@protoc_insertion_point(class_scope:NetworkTest.Query)
 private:
  class _Internal;

  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      0, 1, 0,
      0, 2>
      _table_;
  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {

        inline explicit constexpr Impl_(
            ::google::protobuf::internal::ConstantInitialized) noexcept;
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena);
        inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                              ::google::protobuf::Arena* arena, const Impl_& from);
    ::uint32_t id_;
    mutable ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_NetworkTest_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// Register

// bytes content = 2;
inline void Register::clear_content() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.content_.ClearToEmpty();
}
inline const std::string& Register::content() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:NetworkTest.Register.content)
  return _internal_content();
}
template <typename Arg_, typename... Args_>
inline PROTOBUF_ALWAYS_INLINE void Register::set_content(Arg_&& arg,
                                                     Args_... args) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.content_.SetBytes(static_cast<Arg_&&>(arg), args..., GetArena());
  // @@protoc_insertion_point(field_set:NetworkTest.Register.content)
}
inline std::string* Register::mutable_content() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  std::string* _s = _internal_mutable_content();
  // @@protoc_insertion_point(field_mutable:NetworkTest.Register.content)
  return _s;
}
inline const std::string& Register::_internal_content() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.content_.Get();
}
inline void Register::_internal_set_content(const std::string& value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.content_.Set(value, GetArena());
}
inline std::string* Register::_internal_mutable_content() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  return _impl_.content_.Mutable( GetArena());
}
inline std::string* Register::release_content() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  // @@protoc_insertion_point(field_release:NetworkTest.Register.content)
  return _impl_.content_.Release();
}
inline void Register::set_allocated_content(std::string* value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.content_.SetAllocated(value, GetArena());
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
        if (_impl_.content_.IsDefault()) {
          _impl_.content_.Set("", GetArena());
        }
  #endif  // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:NetworkTest.Register.content)
}

// -------------------------------------------------------------------

// Query

// uint32 id = 1;
inline void Query::clear_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.id_ = 0u;
}
inline ::uint32_t Query::id() const {
  // @@protoc_insertion_point(field_get:NetworkTest.Query.id)
  return _internal_id();
}
inline void Query::set_id(::uint32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:NetworkTest.Query.id)
}
inline ::uint32_t Query::_internal_id() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.id_;
}
inline void Query::_internal_set_id(::uint32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.id_ = value;
}

// -------------------------------------------------------------------

// Result

// uint32 id = 1;
inline void Result::clear_id() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.id_ = 0u;
}
inline ::uint32_t Result::id() const {
  // @@protoc_insertion_point(field_get:NetworkTest.Result.id)
  return _internal_id();
}
inline void Result::set_id(::uint32_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:NetworkTest.Result.id)
}
inline ::uint32_t Result::_internal_id() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.id_;
}
inline void Result::_internal_set_id(::uint32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.id_ = value;
}

// uint32 reason = 2;
inline void Result::clear_reason() {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  _impl_.reason_ = 0u;
}
inline ::uint32_t Result::reason() const {
  // @@protoc_insertion_point(field_get:NetworkTest.Result.reason)
  return _internal_reason();
}
inline void Result::set_reason(::uint32_t value) {
  _internal_set_reason(value);
  // @@protoc_insertion_point(field_set:NetworkTest.Result.reason)
}
inline ::uint32_t Result::_internal_reason() const {
  PROTOBUF_TSAN_READ(&_impl_._tsan_detect_race);
  return _impl_.reason_;
}
inline void Result::_internal_set_reason(::uint32_t value) {
  PROTOBUF_TSAN_WRITE(&_impl_._tsan_detect_race);
  ;
  _impl_.reason_ = value;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace NetworkTest


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // GOOGLE_PROTOBUF_INCLUDED_NetworkTest_2eproto_2epb_2eh
