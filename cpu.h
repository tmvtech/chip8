#ifndef __CPU_H__
#define __CPU_H__

#include <cstdint>

#include "chip8.h"
#include "logger.h"

#define NUM_V_REGISTERS 16
#define PC_START 0x200

class TCpu
{
    // registers
    uint8_t m_reg[NUM_V_REGISTERS];
    uint16_t m_ireg;
    uint16_t m_pcreg;
    uint16_t m_sp_reg;

    // helper variable
    uint16_t m_current_op;              // current opcode being executed
    uint16_t m_instruction;

    TChip8* m_machine;

    // Instructions implementation
    void decode_0_instruction();                        // 0ZZZ
    void clear_screen();                                // 0ZE0
    void return_from_subroutine();                      // 0ZEE
    void jump_to();                                     // 1NNN
    void call_subroutine();                             // 2NNN
    void skip_next_instruction_eq();                    // 3XNN
    void skip_next_instruction_ne();                    // 4XNN
    void skip_next_instruction_vx_vy();                 // 5XYZ
    void register_set();                                // 6XNN
    void add_reg_imm();                                 // 7XNN
    void decode_8_instruction();                        // 8XYZ
    void move_vy_to_vx();                               // 8XY0
    void or_vx_vy();                                    // 8XY1
    void and_vx_vy();                                   // 8XY2
    void xor_vx_vy();                                   // 8XY3
    void add_vx_vy();                                   // 8XY4
    void sub_vx_vy();                                   // 8XY5
    void shift_right_reg();                             // 8XY6
    void subn_vx_vy();                                  // 8XY7
    void shift_left_reg();                              // 8XYE
    void skip_next_instruction_vx_vy_ne();              // 9XYZ
    void set_index_register();                          // ANNN
    void jump_with_v0();                                // BNNN
    void generate_random_number();                      // CXKK
    void draw_sprite();                                 // DXYN
    void decode_E_instruction();                        // EZZZ
    void skip_next_inst_if_key_pressed();               // EX9E
    void skip_next_inst_if_not_pressed();               // EXA1
    void decode_F_instruction();                        // FZZZ
    void load_reg_with_delay_timer();                   // FX07
    void wait_key_press();                              // FX0A
    void load_delay_timer_with_reg();                   // FX15
    void load_sound_timer_with_reg();                   // FX18
    void add_ireg_with_reg();                           // FX1E
    void load_font_from_vx();                           // FX29
    void store_binary_code_decimal_representation();    // FX33
    void load_memory_from_regs();                       // FX55
    void load_regs_from_memory();                       // FX65

    // Logging
    std::shared_ptr<TLogger> m_logger;

public:
    TCpu(TChip8* machine);
    ~TCpu();
    void init();
    void fetch();
    void decode();
    void execute();
    void deinit();
};

#endif
