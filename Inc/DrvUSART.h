//
// DrvUSART.h
//

/// \file DrvUSART.h
/// Funktionen zum Intitialisieren einer USART-Periphery.

#if ! defined(guard_DRV_USART_H)
# define guard_DRV_USART_H

# include <Compiler.h>

# define USART_BAUD_RATE_MIN    1200U
# define USART_BAUD_RATE_MAX    115200U

/// Ergebnis-Code für USART-Funktionen.
typedef enum 
{
  usartSuccess = 0,             ///< Kein Fehler, Funktion erfolgreich ausgeführt.
  usartInvBaudRate,             ///< Ungültige Baud-Rate         
  usartCantSend,                ///< USART kann keine Daten senden, weil die zug. Puffer voll sind.
  usartNoData                   ///< USART hat kein Zeichen im Empfangspuffer.
} UsartResultType;

typedef enum 
{
  usartPort1,
  usartPort2,
  usartPort3
} UsartPortType;

struct __UsartContext;

typedef struct __UsartContext UsartContextType;

typedef UsartContextType volatile * UsartHandleType; // Das 'Handle' ist eine Referenz des zug. Kontextes des USART.

/// Initialisierung eines USART.
/// Der USART wird eingestellt auf 8 Datenbits, jeweils 1 Start-/Stopbit, no parity.
/// \param port gibt den zughörigen USART-Port an.
/// \param baudRate ist die einzustellende Baud-Rate.
/// \return Ergebnis-Code, \sa UsartResultType
UsartResultType InitUsart(UsartPortType port, unsigned baudRate, UsartHandleType * handle);

/// Senden eines einzelnen Zeichens/Datenbytes.
/// \param data ist das Datum, dass zu senden ist.
/// \return Ergebnis-Code, \sa UsartResultType
UsartResultType UsartSend(UsartHandleType handle, BYTE data);

UsartResultType UsartRecv(UsartHandleType handle, BYTE * buffer);

#endif
