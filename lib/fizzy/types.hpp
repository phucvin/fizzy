#pragma once

#include <cstdint>
#include <optional>
#include <string>
#include <vector>


namespace fizzy
{
using bytes = std::basic_string<uint8_t>;
using bytes_view = std::basic_string_view<uint8_t>;

// https://webassembly.github.io/spec/core/binary/types.html#binary-valtype
enum class ValType : uint8_t
{
    i32 = 0x7f,
    i64 = 0x7e,
};

/// The byte meaning an empty wasm result type.
/// https://webassembly.github.io/spec/core/binary/types.html#result-types
constexpr uint8_t BlockTypeEmpty = 0x40;

// https://webassembly.github.io/spec/core/binary/types.html#table-types
constexpr uint8_t FuncRef = 0x70;

// https://webassembly.github.io/spec/core/binary/types.html#binary-functype
struct FuncType
{
    std::vector<ValType> inputs;
    std::vector<ValType> outputs;
};

// https://webassembly.github.io/spec/core/binary/types.html#binary-limits
struct Limits
{
    uint32_t min;
    std::optional<uint32_t> max;
};

// https://webassembly.github.io/spec/core/binary/modules.html#binary-typeidx
using TypeIdx = uint32_t;

// https://webassembly.github.io/spec/core/binary/modules.html#binary-funcidx
using FuncIdx = uint32_t;

// https://webassembly.github.io/spec/core/syntax/modules.html#syntax-tableidx
using TableIdx = uint32_t;

// https://webassembly.github.io/spec/core/syntax/modules.html#syntax-memidx
using MemIdx = uint32_t;

/// Function locals.
/// https://webassembly.github.io/spec/core/binary/modules.html#binary-local
struct Locals
{
    uint32_t count;
    ValType type;
};

enum class Instr : uint8_t
{
    // 5.4.1 Control instructions
    unreachable = 0x00,
    nop = 0x01,
    block = 0x02,
    loop = 0x03,
    if_ = 0x04,
    else_ = 0x05,
    end = 0x0b,
    br = 0x0c,
    br_if = 0x0d,
    br_table = 0x0e,
    return_ = 0x0f,
    call = 0x10,
    call_indirect = 0x11,

    // 5.4.2 Parametric instructions
    drop = 0x1a,
    select = 0x1b,

    // 5.4.3 Variable instructions
    local_get = 0x20,
    local_set = 0x21,
    local_tee = 0x22,
    global_get = 0x23,
    global_set = 0x24,

    // 5.4.4 Memory instructions
    i32_load = 0x28,
    i64_load = 0x29,
    i32_load8_s = 0x2c,
    i32_load8_u = 0x2d,
    i32_load16_s = 0x2e,
    i32_load16_u = 0x2f,
    i64_load8_s = 0x30,
    i64_load8_u = 0x31,
    i64_load16_s = 0x32,
    i64_load16_u = 0x33,
    i64_load32_s = 0x34,
    i64_load32_u = 0x35,
    i32_store = 0x36,
    i64_store = 0x37,
    i32_store8 = 0x3a,
    i32_store16 = 0x3b,
    i64_store8 = 0x3c,
    i64_store16 = 0x3d,
    i64_store32 = 0x3e,
    memory_size = 0x3f,
    memory_grow = 0x40,

    // 5.4.5 Numeric instructions
    i32_const = 0x41,
    i64_const = 0x42,

    i32_eqz = 0x45,
    i32_eq = 0x46,
    i32_ne = 0x47,
    i32_lt_s = 0x48,
    i32_lt_u = 0x49,
    i32_gt_s = 0x4a,
    i32_gt_u = 0x4b,
    i32_le_s = 0x4c,
    i32_le_u = 0x4d,
    i32_ge_s = 0x4e,
    i32_ge_u = 0x4f,

    i64_eqz = 0x50,
    i64_eq = 0x51,
    i64_ne = 0x52,
    i64_lt_s = 0x53,
    i64_lt_u = 0x54,
    i64_gt_s = 0x55,
    i64_gt_u = 0x56,
    i64_le_s = 0x57,
    i64_le_u = 0x58,
    i64_ge_s = 0x59,
    i64_ge_u = 0x5a,

    i32_clz = 0x67,
    i32_ctz = 0x68,
    i32_popcnt = 0x69,
    i32_add = 0x6a,
    i32_sub = 0x6b,
    i32_mul = 0x6c,
    i32_div_s = 0x6d,
    i32_div_u = 0x6e,
    i32_rem_s = 0x6f,
    i32_rem_u = 0x70,
    i32_and = 0x71,
    i32_or = 0x72,
    i32_xor = 0x73,
    i32_shl = 0x74,
    i32_shr_s = 0x75,
    i32_shr_u = 0x76,
    i32_rotl = 0x77,
    i32_rotr = 0x78,

    i64_clz = 0x79,
    i64_ctz = 0x7a,
    i64_popcnt = 0x7b,
    i64_add = 0x7c,
    i64_sub = 0x7d,
    i64_mul = 0x7e,
    i64_div_s = 0x7f,
    i64_div_u = 0x80,
    i64_rem_s = 0x81,
    i64_rem_u = 0x82,
    i64_and = 0x83,
    i64_or = 0x84,
    i64_xor = 0x85,
    i64_shl = 0x86,
    i64_shr_s = 0x87,
    i64_shr_u = 0x88,
    i64_rotl = 0x89,
    i64_rotr = 0x8a,

    i32_wrap_i64 = 0xa7,
    i64_extend_i32_s = 0xac,
    i64_extend_i32_u = 0xad,
};

// https://webassembly.github.io/spec/core/binary/modules.html#table-section
struct Table
{
    Limits limits;
};

// https://webassembly.github.io/spec/core/binary/modules.html#memory-section
struct Memory
{
    Limits limits;
};

struct ConstantExpression
{
    enum class Kind : uint8_t
    {
        Constant,
        GlobalGet
    };

    Kind kind = Kind::Constant;
    union
    {
        uint64_t constant = 0;
        uint32_t global_index;
    } value;
};

// https://webassembly.github.io/spec/core/binary/modules.html#global-section
struct Global
{
    bool is_mutable = false;
    ConstantExpression expression;
};

enum class ExternalKind : uint8_t
{
    Function = 0x00,
    Table = 0x01,
    Memory = 0x02,
    Global = 0x03
};

// https://webassembly.github.io/spec/core/binary/modules.html#import-section
struct Import
{
    std::string module;
    std::string name;
    ExternalKind kind = ExternalKind::Function;
    union
    {
        TypeIdx function_type_index = 0;
        Memory memory;
        bool global_mutable;
        Table table;
    } desc;
};

// https://webassembly.github.io/spec/core/binary/modules.html#export-section
struct Export
{
    std::string name;
    ExternalKind kind = ExternalKind::Function;
    uint32_t index = 0;
};

// https://webassembly.github.io/spec/core/binary/modules.html#element-section
// The table index is omitted from the structure as the parser ensures it to be 0
struct Element
{
    ConstantExpression offset;
    std::vector<FuncIdx> init;
};

// https://webassembly.github.io/spec/core/binary/modules.html#code-section
struct Code
{
    uint32_t local_count = 0;

    // The instructions bytecode without immediate values.
    // https://webassembly.github.io/spec/core/binary/instructions.html
    std::vector<Instr> instructions;

    // The decoded instructions' immediate values.
    // These are instruction-type dependent fixed size value in the order of instructions.
    bytes immediates;
};

// https://webassembly.github.io/spec/core/binary/modules.html#data-section
// The memory index is omitted from the structure as the parser ensures it to be 0
struct Data
{
    ConstantExpression offset;
    bytes init;
};

enum class SectionId : uint8_t
{
    custom = 0,
    type = 1,
    import = 2,
    function = 3,
    table = 4,
    memory = 5,
    global = 6,
    export_ = 7,
    start = 8,
    element = 9,
    code = 10,
    data = 11
};

struct Module
{
    // https://webassembly.github.io/spec/core/binary/modules.html#type-section
    std::vector<FuncType> typesec;
    // https://webassembly.github.io/spec/core/binary/modules.html#import-section
    std::vector<Import> importsec;
    // https://webassembly.github.io/spec/core/binary/modules.html#function-section
    std::vector<TypeIdx> funcsec;
    // https://webassembly.github.io/spec/core/binary/modules.html#table-section
    std::vector<Table> tablesec;
    // https://webassembly.github.io/spec/core/binary/modules.html#memory-section
    std::vector<Memory> memorysec;
    // https://webassembly.github.io/spec/core/binary/modules.html#global-section
    std::vector<Global> globalsec;
    // https://webassembly.github.io/spec/core/binary/modules.html#export-section
    std::vector<Export> exportsec;
    // https://webassembly.github.io/spec/core/binary/modules.html#start-section
    std::optional<FuncIdx> startfunc;
    // https://webassembly.github.io/spec/core/binary/modules.html#element-section
    std::vector<Element> elementsec;
    // https://webassembly.github.io/spec/core/binary/modules.html#code-section
    std::vector<Code> codesec;
    // https://webassembly.github.io/spec/core/binary/modules.html#data-section
    std::vector<Data> datasec;
};

}  // namespace fizzy
